// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include <stdio.h>
#include "model/vector.h"

// https://stackoverflow.com/questions/4120681/how-to-calculate-single-vector-dot-product-using-sse-intrinsic-functions-in-c
scalar_t vec3_dot(v3_t v1, v3_t v2) {
    v3_t r1 = _mm_mul_ps(v1, v2);
    __m128 shuf   = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(2, 3, 0, 1));
    __m128 sums   = _mm_add_ps(r1, shuf);
    shuf          = _mm_movehl_ps(shuf, sums);
    sums          = _mm_add_ss(sums, shuf);
    return _mm_cvtss_f32(sums);
}
