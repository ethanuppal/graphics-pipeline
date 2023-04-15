// Copyright (C) Ethan Uppal 2023. All rights reserved.

#pragma once

#include <math.h> // INFINITY
#include "linalg/vector.h"

typedef struct {
    v3_t p0;
    v3_t p1;
} aabb_t;

#define aabb_maxmin() ((aabb_t){ \
    vec3(INFINITY, INFINITY, INFINITY), \
    vec3(-INFINITY, -INFINITY, -INFINITY), \
})
