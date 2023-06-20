// Copyright (C) Ethan Uppal 2023. All rights reserved.
// benchmark.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graphics.h"

#define WIDTH 500
#define HEIGHT 500

camera3_t camera = camera3(
    .pos = vec3(0, 0, 0),
    .view_width = 2,
    .view_height = 2,
    .z_focus = 1,
    .projection = PROJ_PERSPECTIVE,
    .range = 10
);

#define N 2048
#define NMESH 32
#define NTRI (N / NMESH)
#define NVER (NTRI + 2)

int main() {
    #ifdef DEBUG_COUNTS
    printf("Triangles: %d\nDistributed among meshes: %d\n", N, NMESH);
    #endif

    // Construct the frame buffer.
    frame_buffer_t frame;
    frame_buffer_init(&frame, WIDTH, HEIGHT);

    // Create sample meshes. We leak but that's ok.
    srand48(clock());
    texture_t textures[NMESH];
    mesh3_t meshes[NMESH];
    for (size_t i = 0; i < NMESH; i++) {
        v3_t* vertex_list = malloc(sizeof(*vertex_list) * NVER);
        v3_t low_bound = vec3(
            drand48() * 5 - 2.5,
            drand48() * 5 - 2.5,
            drand48() * 3 + 2
        );
        v3_t high_bound = vec3(
            drand48() * 5 - 2.5,
            drand48() * 5 - 2.5,
            drand48() * 3 + 2
        );
        for (size_t j = 0; j < NVER; j++) {
            vertex_list[j] = vec3_lerp_vec(
                low_bound,
                high_bound,
                vec3(drand48(), drand48(), drand48())
            );
        }
        face3_t* face_list = malloc(sizeof(*face_list) * NTRI);
        for (size_t j = 0; j < NTRI; j++) {
            face_list[j] = face3(j, j + 1, j + 2);
        }
        textures[i] = mono_texture(colorf(drand48(), drand48(), drand48()));
        meshes[i] = mesh3(
            .vertex_count = NVER,
            .vertex_list = vertex_list,
            .face_count = NTRI,
            .face_list = face_list,
            .texture = &textures[i]
        );
    }

    // Cast the rays.
    raycast(&frame, &camera, meshes, lengthof(meshes));

    // Generate ppm file
    ppm_write_frame(stderr, &frame);

    // Free the frame buffer.
    frame_buffer_free(&frame);

    return 0;
}
