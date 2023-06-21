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

color_t water = color24(0, 255, 255);

color_t grass[] = {
    color24(150, 100, 50),
    color24(150, 100, 50),
    color24(0, 255, 0),
    color24(150, 100, 50),
    color24(150, 100, 50),
    color24(150, 100, 50),
};
color_t grass_right[] = {
    color24(150, 100, 50),
    color24(150, 100, 50),
    color24(0, 255, 0),
    color24(150, 100, 50),
    color24(0, 255, 0),
    color24(150, 100, 50),
};

color_t waterfull[] = {
    color24(0, 255, 255),
    color24(0, 255, 255),
    color24(0, 255, 255),
    color24(0, 255, 255),
    color24(0, 255, 255),
    color24(0, 255, 255),
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
    camera.dir.cols[0] = vec3(1, 0, 0);
    camera.dir.cols[1] = vec3(0, cos(theta), sin(theta));
    camera.dir.cols[2] = vec3_cross(
        camera.dir.cols[0],
        camera.dir.cols[1]
    );
    matrix3_multm(yspin(0.3), camera.dir);

    // Create the scene
    common_t* objects[] = {
        common_rect(
            v3(-10, 0, -10),
            v3(10, 0, -10),
            v3(-10, 0, 10),
            v3(10, 0, 10),
            water
        ),
        common_cube(v3(-1, 0, 0), v3(1, 2, 2), grass),
        common_cube(v3(-1.5, 0, 0), v3(-1, 4, -1), grass_right),
        common_cube(v3(-1, 0, -1), v3(0, 1, 0), grass),
        common_cube(v3(1, 0, 1), v3(1.5, 4, 2), grass),
        common_cube(v3(-0.75, 1, -0.5), v3(0.5, 1.5, 0), waterfull),
        common_cube(v3(0, 0, -0.5), v3(0.5, 1, 0), waterfull),
    };
    // Cast the rays.
    mesh3_t meshes[lengthof(objects)];
    for (size_t i = 0; i < lengthof(objects); i++) {
        meshes[i] = *common_get_mesh(objects[i]);
    }
    raycast(&frame, &camera, meshes, lengthof(meshes));

    // Generate ppm file
    ppm_write_frame(stdout, &frame);

    // Free the frame buffer.
    frame_buffer_free(&frame);

    // Free the commons
    for (size_t i = 0; i < lengthof(objects); i++) {
        common_free(objects[i]);
    }

    return 0;
}
