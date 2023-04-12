// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include <stddef.h> // size_t
#include <stdint.h> // uint8_t, uint32_t

typedef uint32_t color_t;
typedef uint8_t depth_t;

#define MAX_DISCRETE_DEPTH ((depth_t)255)
#define CHANNEL_BITMAP ((color_t)0xFF)

/// Represents a projection of 3d space onto a 2d color and depth map.
typedef struct {
    size_t width;
    size_t height;
    color_t* colormap;
    depth_t* depthmap;
} frame_buffer_t;

void frame_buffer_init(frame_buffer_t* frame, size_t width, size_t height);
void frame_buffer_free(frame_buffer_t* frame);

/// Constructs a 24-bit color from the given 8-bit RGB components.
#define color(r, g, b) ( \
    ((color_t)(r) << 24) \
    | ((color_t)(g) << 16) \
    | ((color_t)(b) << 0) \
)
#define color_r(color) (((color) >> 24) & CHANNEL_BITMAP)
#define color_g(color) (((color) >> 16) & CHANNEL_BITMAP)
#define color_b(color) (((color) >> 0) & CHANNEL_BITMAP)
