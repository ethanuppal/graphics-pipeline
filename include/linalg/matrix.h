// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include "linalg/vector.h" // vec3_t

/// Represents a 3x3 matrix.
typedef struct {
    v3_t cols[3];
} matrix3_t;

#define matrix3(a, b, c) ((matrix3_t){{ a, b, c }})

#define matrix3_identity() ((matrix3_t){{ \
    vec3(1, 0 ,0), \
    vec3(0, 1 ,0), \
    vec3(0, 0 ,1) \
}})

/// Computes the determinant of a matrix with the given vectors as its rows or columns.
#define det3(v1, v2, v3) (v1[0] * (v2[1] * v3[2] - v3[1] * v2[2]) \
       - v2[0] * (v1[1] * v3[2] - v3[1] * v1[2]) \
       + v3[0] * (v1[1] * v2[2] - v2[1] * v1[2]))
//scalar_t det3(v3_t v1, v3_t v2, v3_t v3);

// This approach turns out to be slower!
// https://stackoverflow.com/questions/29991373/determinant-calculation-with-simd
// #undef _det3
// #define _det3(v1, v2, v3) vec3_triple(v1, v2, v3)

/// Computes the determinant of the given 3x3 matrix.
#define matrix3_det(m) det3((m).cols[0], (m).cols[1], (m).cols[2])

#define matrix3_apply(matrix, vector) vec3_comb( \
    vector[0], \
    matrix.cols[0], \
    vector[1], \
    matrix.cols[1], \
    vector[2], \
    matrix.cols[2] \
);
#define matrix3_multm(m1, m2) do { \
    m2.cols[0] = matrix3_apply(m1, m2.cols[0]); \
    m2.cols[1] = matrix3_apply(m1, m2.cols[1]); \
    m2.cols[2] = matrix3_apply(m1, m2.cols[2]); \
} while (0)
