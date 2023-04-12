// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include "model/vector.h" // vec3_t
#include "util/macros.h" // GENERIC_CONSTRUCTOR

typedef struct {
    vec3_t pos;

    scalar_t view_width;
    scalar_t view_height;
    scalar_t z_focus;

    scalar_t range;
} camera3_t;

#define camera3(...) GENERIC_CONSTRUCTOR(camera3_t, __VA_ARGS__)
