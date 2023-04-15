// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include <stdio.h>
#include "linalg/vector.h"
#include "util/macros.h" // INLINE

// https://stackoverflow.com/questions/4120681/how-to-calculate-single-vector-dot-product-using-sse-intrinsic-functions-in-c
scalar_t INLINE vec3_dot(v3_t v1, v3_t v2) {
    v3_t r1 = _mm_mul_ps(v1, v2);
    v3_t shuf   = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(2, 3, 0, 1));
    v3_t sums   = _mm_add_ps(r1, shuf);
    shuf          = _mm_movehl_ps(shuf, sums);
    sums          = _mm_add_ss(sums, shuf);
    return _mm_cvtss_f32(sums);
}

scalar_t INLINE vec3_min_e(v3_t v) {
    // v3_t shuf = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 0, 1));
    // v3_t min = _mm_min_ps(v, shuf);
    // shuf = _mm_movehl_ps(min, shuf);
    // min = _mm_min_ps(min, shuf);
    // return _mm_cvtss_f32(min);
    return min(v[0], min(v[1], v[2]));
}

scalar_t INLINE vec3_max_e(v3_t v) {
    // v3_t shuf = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 0, 1));
    // v3_t min = _mm_max_ps(v, shuf);
    // shuf = _mm_movehl_ps(min, shuf);
    // min = _mm_max_ps(min, shuf);
    // return _mm_cvtss_f32(min);
    return max(v[0], max(v[1], v[2]));
}

// https://geometrian.com/programming/tutorials/cross-product/index.php
// v3_t INLINE vec3_cross(v3_t const vec0, v3_t const vec1) {
//     v3_t tmp0 = _mm_shuffle_ps(vec0,vec0,_MM_SHUFFLE(3,0,2,1));
//     v3_t tmp1 = _mm_shuffle_ps(vec1,vec1,_MM_SHUFFLE(3,1,0,2));
//     v3_t tmp2 = _mm_mul_ps(tmp0,vec1);
//     v3_t tmp3 = _mm_mul_ps(tmp0,tmp1);
//     v3_t tmp4 = _mm_shuffle_ps(tmp2,tmp2,_MM_SHUFFLE(3,0,2,1));
//     return _mm_sub_ps(tmp3,tmp4);
// }
