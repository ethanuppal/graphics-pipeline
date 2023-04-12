// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include "model/vector.h" // vec3_t

/// Represents a ray eminating from an arbitary point.
typedef struct {
    /// The source of the ray.
    vec3_t origin;

    /// The normalized direction vector of the ray.
    vec3_t dir;
} ray3_t;

/// Represents the result of a ray intersection.
typedef struct {
    scalar_t t;
    vec2_t loc;
} ray3_intersect;

#define ray3(o, d) ((ray3_t){ o, d });
