// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include "model/vector.h" // vec3_t

/// Represents 3d Euclidean space.
typedef struct {
    vec3_t basis[3];
} space3_t;

/// Represents a 3x3 matrix.
typedef struct {
    vec3_t cols[3];
} matrix3_t;

#define matrix3(a, b, c) ((matrix3_t){{ a, b, c }})
#define m3cols(m) ((m).cols)

#define space3_default() ((space3_t){{ \
    vec3(1, 0 ,0), \
    vec3(0, 1 ,0), \
    vec3(0, 0 ,1) \
}})

#define matrix3_identity() ((matrix3_t){{ \
    vec3(1, 0 ,0), \
    vec3(0, 1 ,0), \
    vec3(0, 0 ,1) \
}})

scalar_t det3(const matrix3_t matrix);

void matrix3_dump(const matrix3_t matrix);
