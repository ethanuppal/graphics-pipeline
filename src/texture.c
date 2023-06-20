// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include "model/texture.h"
#include "model/mesh.h" // mesh3_t, vertex_size_t
#include "model/color.h" // color_t, color_cut

color_t texture_color(const texture_t* texture, ray3_intersect_t* intersection, const camera3_t* camera) {
    color_t color;

    /* Find color */
    switch (texture->type) {
        case TEXTURE_TYPE_MONO: {
            // // Further away = darker; cut off at range
            // depth_t depth_scale = intersection->t / camera->range;
            // if (depth_scale > 1) {
            //     depth_scale = 1;
            // }
            // depth_scale = 1 - depth_scale;

            color = texture->content.mono;
            break;
        }
        case TEXTURE_TYPE_MONO_FACES: {
            color = texture->content.mono_faces[intersection->face];
            break;
        }
    }

    /* Apply lighting */
    // Use inverse square intensity reduction
    // Hacky, will fix to add lights as objects later
    // (Assuming everything is totally transparent, you then just add up all the intensity contributions from each light or something)
    #define T_SCALE 1.0
    // if (intersection->t < 0) {
    //     intensity = 0;
    //     // assuming monodirectional light
    //     // if it isn't then we probably just color it
    // } else {
    //     intensity = T_SCALE / (intersection->t + 1);
    // }
    intersection->t = fabs(intersection->t);
    depth_t intensity = T_SCALE / (intersection->t + 1.0);

    return color * intensity;
}
