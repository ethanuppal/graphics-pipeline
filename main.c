// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include <stdio.h>
#include "graphics.h"

#define WIDTH 10
#define HEIGHT 10

vec3_t vertex_list[] = {
    vec3(-1, -1, 5),
    vec3(0, 1, 5),
    vec3(1, -1, 5),
};
face3_t face_list[] = {
    face3(0, 1, 2)
};
mesh3_t mesh = mesh3(
    .vertex_count = lengthof(vertex_list),
    .vertex_list = vertex_list,
    .face_count = lengthof(face_list),
    .face_list = face_list,
);

camera3_t camera = camera3(
    .pos = vec3(0, 0, 0),
    .view_width = 2,
    .view_height = 2,
    .z_focus = 1,
    .range = 2
);

space3_t space = space3_default();

int main(int argc, char const* argv[]) {
    // Construct the frame buffer.
    frame_buffer_t frame;
    frame_buffer_init(&frame, WIDTH, HEIGHT);

    // Cast the rays.
    mesh3_t meshes[] = {
        mesh
    };
    raycast(&frame, &camera, &space, lengthof(meshes), meshes);

    // Dump the depthmap.
    size_t index = 0;
    for (size_t j = 0; j < frame.height; j++) {
        for (size_t i = 0; i < frame.width; i++) {
            if (i > 0) {
                putchar(' ');
            }
            printf("%03d", frame.depthmap[index]);
            index++;
        }
        putchar('\n');
    }

    // Free the frame buffer.
    frame_buffer_free(&frame);

    return 0;
}
