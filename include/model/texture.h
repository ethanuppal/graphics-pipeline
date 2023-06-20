// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include "model/color.h" // color_t
#include "render/frame_buffer.h" // depth_t
#include "render/camera.h" // camera_t
#include "model/ray.h" // ray3_intersect_t


typedef enum {
    TEXTURE_TYPE_MONO,
    TEXTURE_TYPE_MONO_FACES
} texture_type_t;

/// Represents a texture.
typedef struct {
    texture_type_t type;
    union {
        color_t mono;
        color_t* mono_faces;
    } content;
} texture_t;

#define mono_texture(color) ((texture_t){ \
    .type = TEXTURE_TYPE_MONO, \
    .content = { .mono = (color) } \
})
#define mono_faces_texture(colors) ((texture_t){ \
    .type = TEXTURE_TYPE_MONO_FACES, \
    .content = { .mono_faces = (colors) } \
})

color_t texture_color(const texture_t* texture, ray3_intersect_t* intersection, const camera3_t* camera);
