// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include <stdio.h>
#include "model/vector.h"

vec3_t vec3_add(vec3_t v1, vec3_t v2) {
    vec3_addm(v1, v2);
    return v1;
}

vec3_t vec3_sub(vec3_t v1, vec3_t v2) {
    vec3_subm(v1, v2);
    return v1;
}

vec3_t vec3_comb(scalar_t a, vec3_t v1, scalar_t b, vec3_t v2, scalar_t c, vec3_t v3) {
    vec3_mulm(v1, a);   // a(v1)
    vec3_mulm(v2, b);   // b(v2)
    vec3_mulm(v3, c);   // c(v3)
    vec3_addm(v1, v2);  // a(v1) + b(v2)
    vec3_addm(v1, v3);  // [a(v1) + b(v2)] + c(v3)
    return v1;
}

void vec3_dump(vec3_t v) {
    printf("(vec3){.x=%f, .y=%f, .z=%f}\n", v.x, v.y, v.z);
}
