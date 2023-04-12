// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include "model/vector.h"

/// Represents a triangle in 3d Euclidean space.
typedef struct {
    vec3_t a;
    vec3_t b;
    vec3_t c;
} tri3_t;
