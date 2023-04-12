// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include <stdint.h> // uint32_t

typedef uint32_t color_t;

#define CHANNEL_BITMAP ((color_t)0xFF)
#define RED_BIT_SHIFT 16
#define GREEN_BIT_SHIFT 8
#define BLUE_BIT_SHIFT 0

/// Constructs a 24-bit color from the given 8-bit RGB components.
#define color24(r, g, b) ( \
    ((color_t)(r) << RED_BIT_SHIFT) \
    | ((color_t)(g) << GREEN_BIT_SHIFT) \
    | ((color_t)(b) << BLUE_BIT_SHIFT) \
)

/// Extracts the 8-bit red component from the given color.
#define color_r(color) (((color) >> RED_BIT_SHIFT) & CHANNEL_BITMAP)
/// Extracts the 8-bit green component from the given color.
#define color_g(color) (((color) >> GREEN_BIT_SHIFT) & CHANNEL_BITMAP)
/// Extracts the 8-bit blue component from the given color.
#define color_b(color) (((color) >> BLUE_BIT_SHIFT) & CHANNEL_BITMAP)
