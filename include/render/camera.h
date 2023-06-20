// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include "linalg/vector.h" // vec3_t
#include "linalg/matrix.h" // matrix3_t
#include "util/macros.h" // GENERIC_CONSTRUCTOR

typedef struct {
    v3_t pos;

    scalar_t view_width;
    scalar_t view_height;
    matrix3_t dir;
    enum projection_t {
        PROJ_PARALLEL,
        PROJ_PERSPECTIVE
    } projection;

    scalar_t range;
} camera3_t;

#define camera3(...) GENERIC_CONSTRUCTOR(camera3_t, __VA_ARGS__)
