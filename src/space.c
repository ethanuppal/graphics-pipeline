// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include "model/matrix.h"

#include <stdio.h> // printf

void matrix3_dump(const matrix3_t matrix) {
    const vec3_t* m = matrix.cols;
    printf("[%f %f %f]\n", m[0].x, m[1].x, m[2].x);
    printf("[%f %f %f]\n", m[0].y, m[1].y, m[2].y);
    printf("[%f %f %f]\n", m[0].z, m[1].z, m[2].z);
}
