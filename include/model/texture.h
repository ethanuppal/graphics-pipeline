// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include "model/color.h" // color_t
#include "render/frame_buffer.h" // depth_t
#include "render/camera.h" // camera_t
#include "model/ray.h" // ray3_intersect_t

typedef enum {
    TEXTURE_TYPE_MONO
} texture_type_t;

/// Represents a texture.
typedef struct {
    texture_type_t type;
    union {
        color_t mono;
    } content;
} texture_t;

#define mono_texture(color) ((texture_t){ \
    .type = TEXTURE_TYPE_MONO, \
    .content = { .mono = (color) } \
})

color_t texture_color(const texture_t* texture, ray3_intersect_t* intersection, const camera3_t* camera);
