// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include <stdio.h>
#include <stdbool.h> // bool
#include <math.h> // INFINITY, isfinite
#include "render/raycast.h"
#include "model/vector.h" // vec3_t et al.
#include "model/ray.h" // ray3_t
#include "util/abort.h" // abort
#include "util/macros.h" // INLINE

v3_t tri[3];

INLINE bool single_ray_single_triangle(ray3_intersect* intersect, const ray3_t* ray) {
    // Compute determinants for Cramer's rule
    const v3_t d1 = tri[0] - tri[1];
    const v3_t d2 = tri[0] - tri[2];
    const v3_t d3 = ray->dir;
    const v3_t n = tri[0] - ray->origin;

    const matrix3_t bottom_matrix = matrix3(d1, d2, d3);
    const scalar_t bottom_determinant = det3(bottom_matrix);

    if (bottom_determinant == 0) {
        return false;
    } else {
        const scalar_t beta_determinant = det3(matrix3(n, d2, d3));
        const scalar_t gamma_determinant = det3(matrix3(d1, n, d3));
        const scalar_t t_determinant = det3(matrix3(d1, d2, n));

        // Use Cramer's rule to find barycentric coordinates
        const scalar_t beta = beta_determinant / bottom_determinant;
        const scalar_t gamma = gamma_determinant / bottom_determinant;
        const scalar_t alpha = 1 - beta - gamma;

        // Triangle interior test
        if (alpha > 0 && beta > 0 && gamma > 0) {
            // Convert barycentric to Cartesian
            // https://stackoverflow.com/questions/56328254/how-to-make-the-conversion-from-barycentric-coordinates-to-cartesian-coordinates
            const v3_t barycentric = vec3(alpha, beta, gamma);
            const v3_t tri_x = vec3(tri[0][0], tri[1][0], tri[2][0]);
            const v3_t tri_y = vec3(tri[0][1], tri[1][1], tri[2][1]);
            const scalar_t x = vec3_dot(barycentric, tri_x);
            const scalar_t y = vec3_dot(barycentric, tri_y);

            // Use Cramer's rule to find t
            intersect->t = t_determinant / bottom_determinant;
            intersect->loc = vec2(x, y);

            return true;
        } else {
            return false;
        }
    }
}

void single_ray(color_t* color, depth_t* depth, size_t pi, size_t pj, size_t width, size_t height, const camera3_t* camera, const mesh3_t meshes[], size_t mesh_count);
INLINE void single_ray(color_t* color, depth_t* depth, size_t pi, size_t pj, size_t width, size_t height, const camera3_t* camera, const mesh3_t meshes[], size_t mesh_count) {
    // How far along the plane the x coordinate of the pixel is.
    scalar_t plane_x_prop = (scalar_t)pi / (scalar_t)width;
    // The x coordinate of the pixel on the plane.
    scalar_t plane_x = camera->view_width * (plane_x_prop - 0.5);

    // Invert because of how we index
    scalar_t plane_y_prop = 1 - (scalar_t)pj / (scalar_t)height;
    scalar_t plane_y = camera->view_height * (plane_y_prop - 0.5);

    // The point at which the ray should intersect the plane, also the location
    // of the pixel on the plane, IF ADDED TO camera->pos.
    v3_t plane_intersect = vec3(plane_x, plane_y, camera->z_focus);

    // Normalize the quasi-intersection point to get ray direction.
    v3_t dir = plane_intersect;
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
    color_t chosen;
    for (size_t i = 0; i < mesh_count; i++) {
        const mesh3_t mesh = meshes[i];
        for (size_t j = 0; j < mesh.face_count; j++) {
            mesh3_face_load_tri(tri, &mesh, j);
            ray3_intersect intersect;
            if (single_ray_single_triangle(&intersect, &ray)) {
                if (intersect.t < best_intersect.t) {
                    best_intersect = intersect;
                    chosen = mesh.color;
                }
            }
        }
    }
    if (isfinite(best_intersect.t)) {
        scalar_t normalized_dist = best_intersect.t / camera->range;
        if (normalized_dist > 1) {
            normalized_dist = 1;
        }
        *depth = (depth_t)(normalized_dist * (scalar_t)MAX_DISCRETE_DEPTH);
        *color = chosen;
    }
}

void raycast(frame_buffer_t* frame, const camera3_t* camera, const space3_t* space, const mesh3_t meshes[], size_t mesh_count) {
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
                meshes,
                mesh_count
            );
            index++;
        }
    }
}
