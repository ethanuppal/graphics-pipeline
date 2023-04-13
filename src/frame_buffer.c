// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include <stdlib.h> // malloc, free
#include <string.h> // memset
#include "render/frame_buffer.h"

void frame_buffer_init(frame_buffer_t* frame, size_t width, size_t height) {
    frame->width = width;
    frame->height = height;
    frame->colormap = malloc(sizeof(*frame->colormap) * width * height);
    frame->depthmap = malloc(sizeof(*frame->depthmap) * width * height);
}

void frame_buffer_free(frame_buffer_t* frame) {
    free(frame->colormap);
    free(frame->depthmap);
}

void frame_buffer_clear(frame_buffer_t* frame) {
    const size_t size = frame->width * frame->height;
    memset(frame->colormap, 0, sizeof(*frame->colormap) * size);
    memset(frame->depthmap, 0, sizeof(*frame->depthmap) * size);
}
