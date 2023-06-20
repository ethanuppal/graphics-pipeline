// Copyright (C) 2023 Ethan Uppal. All rights reserved.
#pragma once

#include "model/mesh.h"

// Not meant to be efficient
// Meant to work

#define CUBE_FACES 6
#define CUBE_VERTICES 8
#define RECT_VERTICES 4

typedef struct {
    enum {
        COMMON_TYPE_CUBE,
        COMMON_TYPE_RECT
    } type;
    mesh3_t mesh;
} common_t;

#define common_get_mesh(com) (&(com)->mesh)

common_t* common_cube(v3_t a, v3_t b, color_t face_color[CUBE_FACES]);
common_t* common_rect(v3_t a, v3_t b, v3_t c, v3_t d, color_t color);

void common_free(common_t* com);
