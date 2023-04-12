// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include <stdio.h>
#include "render/ppm.h"
#include "model/color.h" // CHANNEL_BITMAP, color_t et al.

int ppm_write_frame(FILE* dest, const frame_buffer_t* frame) {
    fprintf(dest, "P6\n%zu\n%zu\n%d\n", frame->width, frame->height, CHANNEL_BITMAP);
    size_t index = 0;
    for (size_t j = 0; j < frame->height; j++) {
        for (size_t i = 0; i < frame->width; i++) {
            // TODO: add depth into output
            color_t color = frame->colormap[index];
            depth_t depth_scale = MAX_DISCRETE_DEPTH - frame->depthmap[index];

            color_t r = color_r(color);
            color_t g = color_g(color);
            color_t b = color_b(color);

            r *= depth_scale;
            r /= MAX_DISCRETE_DEPTH;
            g *= depth_scale;
            g /= MAX_DISCRETE_DEPTH;
            b *= depth_scale;
            b /= MAX_DISCRETE_DEPTH;

            fprintf(dest, "%c%c%c", r, g, b);
            index++;
        }
    }
    return 0;
}
