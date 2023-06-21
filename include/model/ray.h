// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include <stddef.h>
#include "linalg/vector.h" // vec3_t

/// Represents a ray eminating from an arbitary point.
typedef struct {
    /// The source of the ray.
    v3_t origin;

    /// The normalized direction vector of the ray.
    v3_t dir;
} ray3_t;

/// Represents the result of a ray intersection.
typedef struct {
    scalar_t t;
    v3_t loc;
    size_t face; // hacky should remove
} ray3_intersect_t;

#define ray3(o, d) ((ray3_t){ o, d });
