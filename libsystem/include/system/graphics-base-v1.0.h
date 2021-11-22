// This file is autogenerated by hidl-gen. Do not edit manually.
// Source: android.hardware.graphics.common@1.0
// Location: hardware/interfaces/graphics/common/1.0/

#ifndef HIDL_GENERATED_ANDROID_HARDWARE_GRAPHICS_COMMON_V1_0_EXPORTED_CONSTANTS_H_
#define HIDL_GENERATED_ANDROID_HARDWARE_GRAPHICS_COMMON_V1_0_EXPORTED_CONSTANTS_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    HAL_PIXEL_FORMAT_RGBA_8888 = 1,
    HAL_PIXEL_FORMAT_RGBX_8888 = 2,
    HAL_PIXEL_FORMAT_RGB_888 = 3,
    HAL_PIXEL_FORMAT_RGB_565 = 4,
    HAL_PIXEL_FORMAT_BGRA_8888 = 5,
    HAL_PIXEL_FORMAT_YCBCR_422_SP = 16,
    HAL_PIXEL_FORMAT_YCRCB_420_SP = 17,
    HAL_PIXEL_FORMAT_YCBCR_422_I = 20,
    HAL_PIXEL_FORMAT_RGBA_FP16 = 22,
    HAL_PIXEL_FORMAT_RAW16 = 32,
    HAL_PIXEL_FORMAT_BLOB = 33,
    HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED = 34,
    HAL_PIXEL_FORMAT_YCBCR_420_888 = 35,
    HAL_PIXEL_FORMAT_RAW_OPAQUE = 36,
    HAL_PIXEL_FORMAT_RAW10 = 37,
    HAL_PIXEL_FORMAT_RAW12 = 38,
    HAL_PIXEL_FORMAT_RGBA_1010102 = 43,
    HAL_PIXEL_FORMAT_Y8 = 538982489,
    HAL_PIXEL_FORMAT_Y16 = 540422489,
    HAL_PIXEL_FORMAT_YV12 = 842094169,
} android_pixel_format_t;

typedef enum {
    HAL_TRANSFORM_FLIP_H = 1,   // (1 << 0)
    HAL_TRANSFORM_FLIP_V = 2,   // (1 << 1)
    HAL_TRANSFORM_ROT_90 = 4,   // (1 << 2)
    HAL_TRANSFORM_ROT_180 = 3,  // (FLIP_H | FLIP_V)
    HAL_TRANSFORM_ROT_270 = 7,  // ((FLIP_H | FLIP_V) | ROT_90)
} android_transform_t;

typedef enum {
    HAL_DATASPACE_UNKNOWN = 0,
    HAL_DATASPACE_ARBITRARY = 1,
    HAL_DATASPACE_STANDARD_SHIFT = 16,
    HAL_DATASPACE_STANDARD_MASK = 4128768,                      // (63 << STANDARD_SHIFT)
    HAL_DATASPACE_STANDARD_UNSPECIFIED = 0,                     // (0 << STANDARD_SHIFT)
    HAL_DATASPACE_STANDARD_BT709 = 65536,                       // (1 << STANDARD_SHIFT)
    HAL_DATASPACE_STANDARD_BT601_625 = 131072,                  // (2 << STANDARD_SHIFT)
    HAL_DATASPACE_STANDARD_BT601_625_UNADJUSTED = 196608,       // (3 << STANDARD_SHIFT)
    HAL_DATASPACE_STANDARD_BT601_525 = 262144,                  // (4 << STANDARD_SHIFT)
    HAL_DATASPACE_STANDARD_BT601_525_UNADJUSTED = 327680,       // (5 << STANDARD_SHIFT)
    HAL_DATASPACE_STANDARD_BT2020 = 393216,                     // (6 << STANDARD_SHIFT)
    HAL_DATASPACE_STANDARD_BT2020_CONSTANT_LUMINANCE = 458752,  // (7 << STANDARD_SHIFT)
    HAL_DATASPACE_STANDARD_BT470M = 524288,                     // (8 << STANDARD_SHIFT)
    HAL_DATASPACE_STANDARD_FILM = 589824,                       // (9 << STANDARD_SHIFT)
    HAL_DATASPACE_STANDARD_DCI_P3 = 655360,                     // (10 << STANDARD_SHIFT)
    HAL_DATASPACE_STANDARD_ADOBE_RGB = 720896,                  // (11 << STANDARD_SHIFT)
    HAL_DATASPACE_TRANSFER_SHIFT = 22,
    HAL_DATASPACE_TRANSFER_MASK = 130023424,       // (31 << TRANSFER_SHIFT)
    HAL_DATASPACE_TRANSFER_UNSPECIFIED = 0,        // (0 << TRANSFER_SHIFT)
    HAL_DATASPACE_TRANSFER_LINEAR = 4194304,       // (1 << TRANSFER_SHIFT)
    HAL_DATASPACE_TRANSFER_SRGB = 8388608,         // (2 << TRANSFER_SHIFT)
    HAL_DATASPACE_TRANSFER_SMPTE_170M = 12582912,  // (3 << TRANSFER_SHIFT)
    HAL_DATASPACE_TRANSFER_GAMMA2_2 = 16777216,    // (4 << TRANSFER_SHIFT)
    HAL_DATASPACE_TRANSFER_GAMMA2_6 = 20971520,    // (5 << TRANSFER_SHIFT)
    HAL_DATASPACE_TRANSFER_GAMMA2_8 = 25165824,    // (6 << TRANSFER_SHIFT)
    HAL_DATASPACE_TRANSFER_ST2084 = 29360128,      // (7 << TRANSFER_SHIFT)
    HAL_DATASPACE_TRANSFER_HLG = 33554432,         // (8 << TRANSFER_SHIFT)
    HAL_DATASPACE_RANGE_SHIFT = 27,
    HAL_DATASPACE_RANGE_MASK = 939524096,      // (7 << RANGE_SHIFT)
    HAL_DATASPACE_RANGE_UNSPECIFIED = 0,       // (0 << RANGE_SHIFT)
    HAL_DATASPACE_RANGE_FULL = 134217728,      // (1 << RANGE_SHIFT)
    HAL_DATASPACE_RANGE_LIMITED = 268435456,   // (2 << RANGE_SHIFT)
    HAL_DATASPACE_RANGE_EXTENDED = 402653184,  // (3 << RANGE_SHIFT)
    HAL_DATASPACE_SRGB_LINEAR = 512,
    HAL_DATASPACE_V0_SRGB_LINEAR = 138477568,  // ((STANDARD_BT709 | TRANSFER_LINEAR) | RANGE_FULL)
    HAL_DATASPACE_V0_SCRGB_LINEAR =
        406913024,  // ((STANDARD_BT709 | TRANSFER_LINEAR) | RANGE_EXTENDED)
    HAL_DATASPACE_SRGB = 513,
    HAL_DATASPACE_V0_SRGB = 142671872,   // ((STANDARD_BT709 | TRANSFER_SRGB) | RANGE_FULL)
    HAL_DATASPACE_V0_SCRGB = 411107328,  // ((STANDARD_BT709 | TRANSFER_SRGB) | RANGE_EXTENDED)
    HAL_DATASPACE_JFIF = 257,
    HAL_DATASPACE_V0_JFIF = 146931712,  // ((STANDARD_BT601_625 | TRANSFER_SMPTE_170M) | RANGE_FULL)
    HAL_DATASPACE_BT601_625 = 258,
    HAL_DATASPACE_V0_BT601_625 =
        281149440,  // ((STANDARD_BT601_625 | TRANSFER_SMPTE_170M) | RANGE_LIMITED)
    HAL_DATASPACE_BT601_525 = 259,
    HAL_DATASPACE_V0_BT601_525 =
        281280512,  // ((STANDARD_BT601_525 | TRANSFER_SMPTE_170M) | RANGE_LIMITED)
    HAL_DATASPACE_BT709 = 260,
    HAL_DATASPACE_V0_BT709 = 281083904,  // ((STANDARD_BT709 | TRANSFER_SMPTE_170M) | RANGE_LIMITED)
    HAL_DATASPACE_DCI_P3_LINEAR = 139067392,  // ((STANDARD_DCI_P3 | TRANSFER_LINEAR) | RANGE_FULL)
    HAL_DATASPACE_DCI_P3 = 155844608,  // ((STANDARD_DCI_P3 | TRANSFER_GAMMA2_6) | RANGE_FULL)
    HAL_DATASPACE_DISPLAY_P3_LINEAR =
        139067392,                         // ((STANDARD_DCI_P3 | TRANSFER_LINEAR) | RANGE_FULL)
    HAL_DATASPACE_DISPLAY_P3 = 143261696,  // ((STANDARD_DCI_P3 | TRANSFER_SRGB) | RANGE_FULL)
    HAL_DATASPACE_ADOBE_RGB = 151715840,  // ((STANDARD_ADOBE_RGB | TRANSFER_GAMMA2_2) | RANGE_FULL)
    HAL_DATASPACE_BT2020_LINEAR = 138805248,  // ((STANDARD_BT2020 | TRANSFER_LINEAR) | RANGE_FULL)
    HAL_DATASPACE_BT2020 = 147193856,     // ((STANDARD_BT2020 | TRANSFER_SMPTE_170M) | RANGE_FULL)
    HAL_DATASPACE_BT2020_PQ = 163971072,  // ((STANDARD_BT2020 | TRANSFER_ST2084) | RANGE_FULL)
    HAL_DATASPACE_DEPTH = 4096,
    HAL_DATASPACE_SENSOR = 4097,
} android_dataspace_t;

typedef enum {
    HAL_COLOR_MODE_INVALID = -1,
    HAL_COLOR_MODE_NATIVE = 0,
    HAL_COLOR_MODE_STANDARD_BT601_625 = 1,
    HAL_COLOR_MODE_STANDARD_BT601_625_UNADJUSTED = 2,
    HAL_COLOR_MODE_STANDARD_BT601_525 = 3,
    HAL_COLOR_MODE_STANDARD_BT601_525_UNADJUSTED = 4,
    HAL_COLOR_MODE_STANDARD_BT709 = 5,
    HAL_COLOR_MODE_DCI_P3 = 6,
    HAL_COLOR_MODE_SRGB = 7,
    HAL_COLOR_MODE_ADOBE_RGB = 8,
    HAL_COLOR_MODE_DISPLAY_P3 = 9,
} android_color_mode_t;

typedef enum {
    HAL_COLOR_TRANSFORM_IDENTITY = 0,
    HAL_COLOR_TRANSFORM_ARBITRARY_MATRIX = 1,
    HAL_COLOR_TRANSFORM_VALUE_INVERSE = 2,
    HAL_COLOR_TRANSFORM_GRAYSCALE = 3,
    HAL_COLOR_TRANSFORM_CORRECT_PROTANOPIA = 4,
    HAL_COLOR_TRANSFORM_CORRECT_DEUTERANOPIA = 5,
    HAL_COLOR_TRANSFORM_CORRECT_TRITANOPIA = 6,
} android_color_transform_t;

typedef enum {
    HAL_HDR_DOLBY_VISION = 1,
    HAL_HDR_HDR10 = 2,
    HAL_HDR_HLG = 3,
} android_hdr_t;

#ifdef __cplusplus
}
#endif

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_GRAPHICS_COMMON_V1_0_EXPORTED_CONSTANTS_H_
