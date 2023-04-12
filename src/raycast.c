// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include <stdio.h>
#include <stdbool.h> // bool
#include <math.h> // INFINITY, isfinite
#include "render/raycast.h"
#include "model/vector.h" // vec3_t et al.
#include "model/ray.h" // ray3_t
#include "util/abort.h" // abort

bool single_ray_single_triangle(ray3_intersect* intersect, const ray3_t* ray, const tri3_t* tri) {

}

void single_ray(color_t* color, depth_t* depth, size_t pi, size_t pj, size_t width, size_t height, const camera3_t* camera, size_t mesh_count, const mesh3_t meshes[]) {
    // How far along the plane the x coordinate of the pixel is.
    scalar_t plane_x_prop = (scalar_t)pi / (scalar_t)width;
    // The x coordinate of the pixel on the plane.
    scalar_t plane_x = camera->view_width * (plane_x_prop - 0.5);

    scalar_t plane_y_prop = (scalar_t)pj / (scalar_t)height;
    scalar_t plane_y = camera->view_height * (plane_y_prop - 0.5);

    // The point at which the ray should intersect the plane, also the location
    // of the pixel on the plane, IF ADDED TO camera->pos.
    vec3_t plane_intersect = vec3(plane_x, plane_y, camera->z_focus);

    // Normalize the quasi-intersection point to get ray direction.
    vec3_t dir = plane_intersect;
    vec3_normm(dir);

    // Create the ray.
    const ray3_t ray = ray3(camera->pos, dir);

    // Make depth map distance to view plane for testing
    // vec3_subm(plane_intersect, camera->pos);
    // *depth = (depth_t)(vec3_mag(plane_intersect)
    //                    / camera->range
    //                    * (scalar_t)MAX_DISCRETE_DEPTH);

    ray3_intersect best_intersect;
    best_intersect.t = INFINITY;
    for (size_t i = 0; i < mesh_count; i++) {
        const mesh3_t mesh = meshes[i];
        for (size_t j = 0; j < mesh.face_count; j++) {
            const tri3_t tri = mesh3_face_tri(&mesh, j);
            ray3_intersect intersect;
            if (single_ray_single_triangle(&intersect, &ray, &tri)) {
                if (intersect.t < best_intersect.t) {
                    best_intersect = intersect;
                }
            }
        }
    }
    if (isfinite(best_intersect.t)) {
        *depth = 1;
    }
}

void raycast(frame_buffer_t* frame, const camera3_t* camera, const space3_t* space, size_t mesh_count, const mesh3_t meshes[]) {
    size_t index = 0;
    for (size_t j = 0; j < frame->height; j++) {
        for (size_t i = 0; i < frame->width; i++) {
            single_ray(
                &frame->colormap[index],
                &frame->depthmap[index],
                i,
                j,
                frame->width,
                frame->height,
                camera,
                mesh_count,
                meshes
            );
            index++;
        }
    }
}
