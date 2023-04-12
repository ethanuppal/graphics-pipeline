// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include "model/space.h"

// https://dcvp84mxptlac.cloudfront.net/diagrams2/equation-3-determinant-of-a-3x3-matrix.png
// Probably has mistakes
inline scalar_t det3(const matrix3_t matrix) {
    const vec3_t* m = m3cols(matrix);
    return m[0].x * (m[1].y * m[2].z - m[2].y * m[1].z)
           - m[1].x * (m[0].y * m[2].z - m[2].y * m[0].z)
           + m[2].x * (m[0].y * m[1].z - m[1].y * m[0].z);
}

#include <stdio.h> // printf

void matrix3_dump(const matrix3_t matrix) {
    const vec3_t* m = m3cols(matrix);
    printf("[%f %f %f]\n", m[0].x, m[1].x, m[2].x);
    printf("[%f %f %f]\n", m[0].y, m[1].y, m[2].y);
    printf("[%f %f %f]\n", m[0].z, m[1].z, m[2].z);
}
