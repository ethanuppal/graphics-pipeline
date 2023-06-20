// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include "linalg/vector.h" // scalar_t

typedef v3_t color_t;

// #define CHANNEL_BITMAP ((color_t)0xFF)
// #define RED_BIT_SHIFT 16
// #define GREEN_BIT_SHIFT 8
// #define BLUE_BIT_SHIFT 0

#define COLOR24_SCALE ((scalar_t)(255.0))

/// Constructs a 24-bit color from the given 8-bit RGB components.
#define color24(r, g, b) ((color_t){ \
    (r) / COLOR24_SCALE, \
    (g) / COLOR24_SCALE, \
    (b) / COLOR24_SCALE \
})

#define colorf(r, g, b) ((color_t){ r, g, b })

/// Extracts the 8-bit red component from the given color.
#define color_r(color) ((color)[0])
/// Extracts the 8-bit green component from the given color.
#define color_g(color) ((color)[1])
/// Extracts the 8-bit blue component from the given color.
#define color_b(color) ((color)[2])

#define color_cut(color) (_mm_min_ps(color, v3(1, 1, 1)))

// https://en.wikipedia.org/wiki/Relative_luminance
#define color_luma(color) ( \
    (0.2126 * color_r(color)) \
    + (0.7152 * color_g(color)) \
    + (0.0722 * color_b(color)) \
)

#define color_set_luma(color, luma) do { \
    (color) /= (scalar_t)color_luma(color); \
    (color) *= _mm_set1_ps(luma); \
    (color) = color_cut(color); \
} while (0)
