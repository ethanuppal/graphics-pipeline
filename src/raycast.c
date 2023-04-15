// Copyright (C) Ethan Uppal 2023. All rights reserved.

//#include <stdio.h>
#include <stdbool.h> // bool
#include <math.h> // INFINITY, isfinite
#include "render/raycast.h"
#include "linalg/vector.h" // vec3_t et al.
#include "linalg/matrix.h" // det3
#include "model/ray.h" // ray3_t
#include "util/abort.h" // abort
#include "util/macros.h" // INLINE, min, max
#include "model/texture.h" // texture_color

bool per_pixel_ray_single_triangle(ray3_intersect_t* intersection, const ray3_t* ray, v3_t tri[3]);
void raycast_determine_ray(ray3_t* ray,  size_t pi, size_t pj, size_t width, size_t height, const camera3_t* camera);
void find_ray_intersections(ray3_intersect_t* best_intersection, const texture_t** chosen, const ray3_t* ray, const mesh3_internal_t meshes[], size_t mesh_count);
void per_pixel_ray(color_t* color, depth_t* depth, size_t pi, size_t pj, size_t width, size_t height, const camera3_t* camera, const mesh3_internal_t meshes[], size_t mesh_count);
bool ray_intersects_aabb(const ray3_t* ray, const aabb_t* aabb);

bool INLINE per_pixel_ray_single_triangle(ray3_intersect_t* intersection, const ray3_t* ray, v3_t tri[VECTORS_PER_TRI]) {
    // Compute determinants for Cramer's rule
    const v3_t n = tri[0] - ray->origin;
    const v3_t d1 = tri[1];
    const v3_t d2 = tri[2];
    const v3_t d3 = ray->dir;

    const scalar_t bottom_determinant = det3(d1, d2, d3);

    if (bottom_determinant == 0) {
        return false;
    } else {
        const scalar_t beta_determinant = det3(n, d2, d3);
        const scalar_t gamma_determinant = det3(d1, n, d3);
        const scalar_t t_determinant = det3(d1, d2, n);

        // Use Cramer's rule to find barycentric coordinates
        const scalar_t beta = beta_determinant / bottom_determinant;
        const scalar_t gamma = gamma_determinant / bottom_determinant;
        const scalar_t alpha = 1 - beta - gamma;

        // Triangle interior test
        if (alpha > 0 && beta > 0 && gamma > 0) {
            // Convert barycentric to Cartesian
            // https://stackoverflow.com/questions/56328254/how-to-make-the-conversion-from-barycentric-coordinates-to-cartesian-coordinates
            // const v3_t barycentric = vec3(alpha, beta, gamma);
            // const v3_t tri_x = vec3(tri[0][0], tri[1][0], tri[2][0]);
            // const v3_t tri_y = vec3(tri[0][1], tri[1][1], tri[2][1]);
            // const scalar_t x = vec3_dot(barycentric, tri_x);
            // const scalar_t y = vec3_dot(barycentric, tri_y);

            // Use Cramer's rule to find t
            intersection->t = t_determinant / bottom_determinant;
            intersection->loc = vec2(beta, gamma);

            return true;
        } else {
            return false;
        }
    }
}

void INLINE raycast_determine_ray(ray3_t* ray,  size_t pi, size_t pj, size_t width, size_t height, const camera3_t* camera) {
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
    *ray = ray3(camera->pos, dir);
}

// https://www.rose-hulman.edu/class/csse/csse451/AABB/
// https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms#18459
bool INLINE ray_intersects_aabb(const ray3_t* ray, const aabb_t* aabb) {
    const v3_t tp0_vec = (aabb->p0 - ray->origin) / ray->dir;
    const v3_t tp1_vec = (aabb->p1 - ray->origin) / ray->dir;

    const scalar_t tmin = min(vec3_min_e(tp0_vec), vec3_min_e(tp1_vec));
    const scalar_t tmax = max(vec3_max_e(tp0_vec), vec3_max_e(tp1_vec));

    if (tmax < 0) {
        return false;
    } else if (tmin > tmax) {
        return false;
    } else {
        return true;
    }
}

void INLINE find_ray_intersections(ray3_intersect_t* best_intersection, const texture_t** chosen, const ray3_t* ray, const mesh3_internal_t meshes[], size_t mesh_count) {
    best_intersection->t = INFINITY;

    // Check each triangle for intersection and use the closest one.
    ray3_intersect_t current_intersection;
    for (size_t i = 0; i < mesh_count; i++) {
        const mesh3_internal_t mesh = meshes[i];
        if (ray_intersects_aabb(ray, &mesh.aabb)) {
            for (size_t j = 0; j < mesh.size; j += VECTORS_PER_TRI) {
                if (per_pixel_ray_single_triangle(&current_intersection, ray, &mesh.triangles[j])) {
                    if (current_intersection.t < best_intersection->t) {
                        *chosen = mesh.texture;
                        *best_intersection = current_intersection;
                    }
                }
            }
        }
    }
}

INLINE void per_pixel_ray(color_t* color, depth_t* depth, size_t pi, size_t pj, size_t width, size_t height, const camera3_t* camera, const mesh3_internal_t meshes[], size_t mesh_count) {
    // -- Part 1: Determine the ray corresponding to the pixel.
    ray3_t ray;
    raycast_determine_ray(&ray, pi, pj, width, height, camera);

    // -- Part 2: Cast rays and z-sort.
    ray3_intersect_t best_intersection;
    const texture_t* texture;
    find_ray_intersections(
        &best_intersection,
        &texture,
        &ray,
        meshes,
        mesh_count
    );

    // -- Part 3: If the ray hit something, indicate so in the frame buffer.
    if (isfinite(best_intersection.t)) {
        *depth = best_intersection.t;
        *color = texture_color(texture, &best_intersection, camera);
    }
}

void raycast(frame_buffer_t* frame, const camera3_t* camera, const mesh3_t meshes[], size_t mesh_count) {
    // Turn the mesh into an internal triangle representation.
    mesh3_internal_t* mesh_internals = create_mesh_internals(
        meshes,
        mesh_count
    );

    // Cast a ray for each pixel.
    size_t index = 0;
    for (size_t j = 0; j < frame->height; j++) {
        for (size_t i = 0; i < frame->width; i++) {
            per_pixel_ray(
                &frame->colormap[index],
                &frame->depthmap[index],
                i,
                j,
                frame->width,
                frame->height,
                camera,
                mesh_internals,
                mesh_count
            );
            index++;
        }
    }

    // Free the internal triangle representation.
    free_mesh_internals(mesh_internals, mesh_count);
}
