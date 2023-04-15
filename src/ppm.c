// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include <stdio.h>
#include <stdint.h> // uint8_t
#include "render/ppm.h"
#include "model/color.h" // COLOR24_SCALE, color_t et al.

int ppm_write_frame(FILE* dest, const frame_buffer_t* frame) {
    fprintf(dest, "P6\n%zu\n%zu\n%d\n", frame->width, frame->height, 255);
    size_t index = 0;
    for (size_t j = 0; j < frame->height; j++) {
        for (size_t i = 0; i < frame->width; i++) {
            // TODO: add depth into output
            color_t color = frame->colormap[index];

            uint8_t r = color_r(color) * COLOR24_SCALE;
            uint8_t g = color_g(color) * COLOR24_SCALE;
            uint8_t b = color_b(color) * COLOR24_SCALE;

            fprintf(dest, "%c%c%c", r, g, b);
            index++;
        }
    }
    return 0;
}
