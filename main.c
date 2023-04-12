// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include <stdio.h>
#include "graphics.h"

#define WIDTH 500
#define HEIGHT 500

vec3_t vertex_list1[] = {
    vec3(-2, -1, 2.5),
    vec3(-0.5, 1, 5.5),
    vec3(1, -1, 4.5),
};
face3_t face_list1[] = {
    face3(0, 1, 2)
};
mesh3_t mesh1 = mesh3(
    .vertex_count = lengthof(vertex_list1),
    .vertex_list = vertex_list1,
    .face_count = lengthof(face_list1),
    .face_list = face_list1,
    .color = color24(255, 0, 0)
);

vec3_t vertex_list2[] = {
    vec3(-1, 1, 2.5),
    vec3(1.5, 2.5, 3.5),
    vec3(2, 0.8, 2.5),
};
face3_t face_list2[] = {
    face3(0, 1, 2)
};
mesh3_t mesh2 = mesh3(
    .vertex_count = lengthof(vertex_list2),
    .vertex_list = vertex_list2,
    .face_count = lengthof(face_list2),
    .face_list = face_list2,
    .color = color24(255, 255, 0)
);

vec3_t vertex_list3[] = {
    vec3(1, -1, 4.5),
    vec3(-1, -1, 2.5),
    vec3(1.5, 2.5, 3.5),
};
face3_t face_list3[] = {
    face3(0, 1, 2)
};
mesh3_t mesh3_ = mesh3(
    .vertex_count = lengthof(vertex_list3),
    .vertex_list = vertex_list3,
    .face_count = lengthof(face_list3),
    .face_list = face_list3,
    .color = color24(0, 100, 255)
);

camera3_t camera = camera3(
    .pos = vec3(0, 0, 0),
    .view_width = 2,
    .view_height = 2,
    .z_focus = 1,
    .range = 10
);

space3_t space = space3_default();

int main(int argc, char const* argv[]) {
    // Construct the frame buffer.
    frame_buffer_t frame;
    frame_buffer_init(&frame, WIDTH, HEIGHT);

    // Cast the rays.
    mesh3_t meshes[] = {
        mesh1, mesh2, mesh3_
    };
    raycast(&frame, &camera, &space, lengthof(meshes), meshes);

    // Generate ppm file
    ppm_write_frame(stdout, &frame);

    // Free the frame buffer.
    frame_buffer_free(&frame);

    return 0;
}
