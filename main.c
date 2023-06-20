// @copy Copyright (C) Ethan Uppal 2023. All rights reserved.
// @file This program draws a red cube using parallel projection.

#include <stdio.h>
#include <math.h>
#include "graphics.h"
#include "common/common.h"

#define WIDTH 500
#define HEIGHT 500

// Parallel projection from (0, 0, 0) to 2x2 window centered at (0,0,1)
camera3_t camera = camera3(
    .pos = vec3(0, 2, -0.5),
    .view_width = 5,
    .view_height = 5,
    .projection = PROJ_PARALLEL
);

color_t face_colors[] = {
    color24(255, 0, 0),
    color24(0, 255, 0),
    color24(255, 255, 0),
    color24(255, 0, 0),
    color24(0, 255, 0),
    color24(255, 255, 0),
};

#define yspin(theta) matrix3( \
    vec3(cos(theta), 0, sin(theta)), \
    vec3(0, 1, 0), \
    vec3(-sin(theta), 0, cos(theta)) \
)
#define xspin(theta) matrix3( \
    vec3(1, 0, 0), \
    vec3(0, cos(theta), sin(theta)), \
    vec3(0, -sin(theta), cos(theta)) \
)

int main(void) {
    // Construct the frame buffer.
    frame_buffer_t frame;
    frame_buffer_init(&frame, WIDTH, HEIGHT);

    // Orient camera
    scalar_t theta = 0.2;
    scalar_t theta2 = -0.2;
    camera.dir.cols[0] = vec3(1, 0, 0);
    camera.dir.cols[1] = vec3(0, cos(theta), sin(theta));
    camera.dir.cols[2] = vec3_cross(
        camera.dir.cols[0],
        camera.dir.cols[1]
    );
    matrix3_multm(yspin(0.3), camera.dir);
    // matrix3_multm(xspin(0.3), camera.dir);

    // Surface
    common_t* surface = common_rect(
        v3(-2, 0, -10),
        v3(2, 0, -10),
        v3(-2, 0, 10),
        v3(2, 0, 10),
        color24(200, 200, 200)
    );
    mesh3_t* surface_mesh = common_get_mesh(surface);

    // Create the cube
    common_t* cube1 = common_cube(v3(-1, 0, 0), v3(1, 2, 2), face_colors);
    mesh3_t* cube1_mesh = common_get_mesh(cube1);

    common_t* cube2 = common_cube(v3(-1, 0, -1), v3(0, 1, 0), face_colors);
    mesh3_t* cube2_mesh = common_get_mesh(cube2);

    // Cast the rays.
    mesh3_t meshes[] = { *surface_mesh, *cube1_mesh, *cube2_mesh };
    raycast(&frame, &camera, meshes, lengthof(meshes));

    // Generate ppm file
    ppm_write_frame(stdout, &frame);

    // Free the frame buffer.
    frame_buffer_free(&frame);

    // Free the commons
    common_free(cube1);
    common_free(cube2);
    common_free(surface);

    return 0;
}
