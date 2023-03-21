//
// Copyright (C) 2023 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "task.h"
#include <iostream>
#include "fastboot.h"
#include "filesystem.h"
#include "super_flash_helper.h"

using namespace std::string_literals;
FlashTask::FlashTask(const std::string& _slot, const std::string& _pname, const std::string& _fname,
                     const bool apply_vbmeta)
    : pname_(_pname), fname_(_fname), slot_(_slot), apply_vbmeta_(apply_vbmeta) {}

void FlashTask::Run() {
    auto flash = [&](const std::string& partition) {
        if (should_flash_in_userspace(partition) && !is_userspace_fastboot()) {
            die("The partition you are trying to flash is dynamic, and "
                "should be flashed via fastbootd. Please run:\n"
                "\n"
                "    fastboot reboot fastboot\n"
                "\n"
                "And try again. If you are intentionally trying to "
                "overwrite a fixed partition, use --force.");
        }
        do_flash(partition.c_str(), fname_.c_str(), apply_vbmeta_);
    };
    do_for_partitions(pname_, slot_, flash, true);
}

RebootTask::RebootTask(FlashingPlan* fp) : fp_(fp){};
RebootTask::RebootTask(FlashingPlan* fp, const std::string& reboot_target)
    : reboot_target_(reboot_target), fp_(fp){};

void RebootTask::Run() {
    if ((reboot_target_ == "userspace" || reboot_target_ == "fastboot")) {
        if (!is_userspace_fastboot()) {
            reboot_to_userspace_fastboot();
            fp_->fb->WaitForDisconnect();
        }
    } else if (reboot_target_ == "recovery") {
        fp_->fb->RebootTo("recovery");
        fp_->fb->WaitForDisconnect();
    } else if (reboot_target_ == "bootloader") {
        fp_->fb->RebootTo("bootloader");
        fp_->fb->WaitForDisconnect();
    } else if (reboot_target_ == "") {
        fp_->fb->Reboot();
        fp_->fb->WaitForDisconnect();
    } else {
        syntax_error("unknown reboot target %s", reboot_target_.c_str());
    }
}

FlashSuperLayoutTask::FlashSuperLayoutTask(const std::string& super_name,
                                           std::unique_ptr<SuperFlashHelper> helper,
                                           SparsePtr sparse_layout)
    : super_name_(super_name),
      helper_(std::move(helper)),
      sparse_layout_(std::move(sparse_layout)) {}

void FlashSuperLayoutTask::Run() {
    std::vector<SparsePtr> files;
    if (int limit = get_sparse_limit(sparse_file_len(sparse_layout_.get(), false, false))) {
        files = resparse_file(sparse_layout_.get(), limit);
    } else {
        files.emplace_back(std::move(sparse_layout_));
    }

    // Send the data to the device.
    flash_partition_files(super_name_, files);
}

std::unique_ptr<FlashSuperLayoutTask> FlashSuperLayoutTask::Initialize(
        FlashingPlan* fp, std::vector<ImageEntry>& os_images) {
    if (!supports_AB()) {
        LOG(VERBOSE) << "Cannot optimize flashing super on non-AB device";
        return nullptr;
    }
    if (fp->slot == "all") {
        LOG(VERBOSE) << "Cannot optimize flashing super for all slots";
        return nullptr;
    }

    // Does this device use dynamic partitions at all?
    unique_fd fd = fp->source->OpenFile("super_empty.img");

    if (fd < 0) {
        LOG(VERBOSE) << "could not open super_empty.img";
        return nullptr;
    }

    std::string super_name;
    // Try to find whether there is a super partition.
    if (fp->fb->GetVar("super-partition-name", &super_name) != fastboot::SUCCESS) {
        super_name = "super";
    }
    std::string partition_size_str;

    if (fp->fb->GetVar("partition-size:" + super_name, &partition_size_str) != fastboot::SUCCESS) {
        LOG(VERBOSE) << "Cannot optimize super flashing: could not determine super partition";
        return nullptr;
    }
    std::unique_ptr<SuperFlashHelper> helper = std::make_unique<SuperFlashHelper>(*fp->source);
    if (!helper->Open(fd)) {
        return nullptr;
    }

    for (const auto& entry : os_images) {
        auto partition = GetPartitionName(entry, fp->current_slot);
        auto image = entry.first;

        if (!helper->AddPartition(partition, image->img_name, image->optional_if_no_image)) {
            return nullptr;
        }
    }

    auto s = helper->GetSparseLayout();
    if (!s) return nullptr;

    // Remove images that we already flashed, just in case we have non-dynamic OS images.
    auto remove_if_callback = [&](const ImageEntry& entry) -> bool {
        return helper->WillFlash(GetPartitionName(entry, fp->current_slot));
    };
    os_images.erase(std::remove_if(os_images.begin(), os_images.end(), remove_if_callback),
                    os_images.end());
    return std::make_unique<FlashSuperLayoutTask>(super_name, std::move(helper), std::move(s));
}

UpdateSuperTask::UpdateSuperTask(FlashingPlan* fp) : fp_(fp) {}

void UpdateSuperTask::Run() {
    unique_fd fd = fp_->source->OpenFile("super_empty.img");
    if (fd < 0) {
        return;
    }
    if (!is_userspace_fastboot()) {
        reboot_to_userspace_fastboot();
    }

    std::string super_name;
    if (fp_->fb->GetVar("super-partition-name", &super_name) != fastboot::RetCode::SUCCESS) {
        super_name = "super";
    }
    fp_->fb->Download(super_name, fd, get_file_size(fd));

    std::string command = "update-super:" + super_name;
    if (fp_->wants_wipe) {
        command += ":wipe";
    }
    fp_->fb->RawCommand(command, "Updating super partition");
}

ResizeTask::ResizeTask(FlashingPlan* fp, const std::string& pname, const std::string& size,
                       const std::string& slot)
    : fp_(fp), pname_(pname), size_(size), slot_(slot) {}

void ResizeTask::Run() {
    auto resize_partition = [this](const std::string& partition) -> void {
        if (is_logical(partition)) {
            fp_->fb->ResizePartition(partition, size_);
        }
    };
    do_for_partitions(pname_, slot_, resize_partition, false);
}

DeleteTask::DeleteTask(FlashingPlan* fp, const std::string& pname) : fp_(fp), pname_(pname){};

void DeleteTask::Run() {
    fp_->fb->DeletePartition(pname_);
}

WipeTask::WipeTask(FlashingPlan* fp, const std::string& pname) : fp_(fp), pname_(pname){};

void WipeTask::Run() {
    std::string partition_type;
    if (fp_->fb->GetVar("partition-type:" + pname_, &partition_type) != fastboot::SUCCESS) {
        return;
    }
    if (partition_type.empty()) return;
    fp_->fb->Erase(pname_);
    fb_perform_format(pname_, 1, partition_type, "", fp_->fs_options);
}
