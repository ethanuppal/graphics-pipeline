// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include "model/texture.h"

color_t texture_color(const texture_t* texture, ray3_intersect_t* intersection, const camera3_t* camera) {
    switch (texture->type) {
        case TEXTURE_TYPE_MONO: {
            // Further away = darker; cut off at range
            depth_t depth_scale = intersection->t / camera->range;
            if (depth_scale > 1) {
                depth_scale = 1;
            }
            depth_scale = 1 - depth_scale;

            return texture->content.mono * depth_scale;
        }
    }
}
