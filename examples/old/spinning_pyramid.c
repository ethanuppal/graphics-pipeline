// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include <stdio.h>
#include <math.h> // sin, cos
#include <stdlib.h> // malloc, free
#include "graphics.h"

#define WIDTH 500
#define HEIGHT 400

vec3_t vertex_list1[] = {
    vec3(-1, -1, 2),
    vec3(0, -1, 4),
    vec3(1, -1, 2),
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
    vec3(-1, -1, 2),
    vec3(0, 1, 2),
    vec3(0, -1, 4),
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
    vec3(1, -1, 2),
    vec3(0, 1, 2),
    vec3(0, -1, 4),
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
    .view_height = 2.0 * 4.0 / 5.0,
    .z_focus = 1,
    .range = 10
);

space3_t space = space3_default();

// Only deep-copies verticies
void meshes_deep_copy_vertices(mesh3_t dests[], const mesh3_t srcs[], size_t length) {
    for (size_t i = 0; i < length; i++) {
        mesh3_t* dest = &dests[i];
        const mesh3_t* src = &srcs[i];

        dest->vertex_count = src->vertex_count;
        dest->vertex_list = malloc(sizeof(*dest->vertex_list) * src->vertex_count);

        for (size_t j = 0; j < src->vertex_count; j++) {
            // struct copying = deep copy
            dest->vertex_list[j] = src->vertex_list[j];
        }

        dest->face_count = src->face_count;
        dest->face_list = src->face_list;
        dest->color = src->color;
    }
}

void render_with_angle(frame_buffer_t* frame, scalar_t theta, size_t i, mesh3_t meshes[], size_t mesh_count) {
    mesh3_t meshes_copy[mesh_count];
    meshes_deep_copy_vertices(meshes_copy, meshes, mesh_count);

    // Rotate by theta and raycast
    for (size_t j = 0; j < mesh_count; j++) {
        mesh3_transform(
            &meshes_copy[j],
            vec3(0, -1, 3),
            matrix3(
                vec3(cos(theta), 0, sin(theta)),
                vec3(0, 1, 0),
                vec3(-sin(theta), 0, cos(theta))
            )
        );
    }
    raycast(frame, &camera, &space, meshes_copy, mesh_count);

    // Generate ppm file
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "./bin/out_%zu.ppm", i);
    FILE* dest = fopen(buffer, "w");
    ppm_write_frame(dest, frame);
    fclose(dest);

    frame_buffer_clear(frame);
    for (size_t i = 0; i < mesh_count; i++) {
        free(meshes_copy[i].vertex_list);
    }
}

#define N 60
int main(int argc, char const* argv[]) {
    // Construct the frame buffer.
    frame_buffer_t frame;
    frame_buffer_init(&frame, WIDTH, HEIGHT);

    // Cast the rays.
    mesh3_t meshes[] = {
        mesh1, mesh2, mesh3_
    };
    // Try all rotations around y axis
    scalar_t delta_theta = (scalar_t)M_PI / (scalar_t)N * 2;
    scalar_t theta = 0;
    for (size_t i = 0; i < N; i++) {
        render_with_angle(&frame, theta, i, meshes, lengthof(meshes));
        theta += delta_theta;
    }

    // Free the frame buffer.
    frame_buffer_free(&frame);

    return 0;
}
