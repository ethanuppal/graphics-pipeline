// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include <stddef.h> // size_t
#include "model/color.h" // color_t
#include "linalg/vector.h" // scalar_t

typedef scalar_t depth_t;

// #define MAX_DISCRETE_DEPTH ((depth_t)255)

/// Represents a projection of 3d space onto a 2d color and depth map.
typedef struct {
    size_t width;
    size_t height;
    color_t* colormap;
    depth_t* depthmap;
} frame_buffer_t;

void frame_buffer_init(frame_buffer_t* frame, size_t width, size_t height);
void frame_buffer_free(frame_buffer_t* frame);

void frame_buffer_clear(frame_buffer_t* frame);
