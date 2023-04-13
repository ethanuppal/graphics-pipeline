// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include "model/vector.h" // vec3_t

/// Represents 3d Euclidean space.
typedef struct {
    v3_t basis[3];
} space3_t;

/// Represents a 3x3 matrix.
typedef struct {
    v3_t cols[3];
} matrix3_t;

#define matrix3(a, b, c) ((matrix3_t){{ a, b, c }})

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

// https://dcvp84mxptlac.cloudfront.net/diagrams2/equation-3-determinant-of-a-3x3-matrix.png
#define det3(matrix) det3_cols((matrix).cols)
#define det3_cols(m) (m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) \
       - m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2]) \
       + m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]))

void matrix3_dump(const matrix3_t matrix);
