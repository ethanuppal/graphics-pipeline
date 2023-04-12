// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include <math.h> // sqrt

typedef float scalar_t;

/// Represents a vector in 3d Euclidean space.
typedef struct {
    scalar_t x;
    scalar_t y;
    scalar_t z;
} vec3_t;

/// Creates a 3d vector with the given components.
#define vec3(x, y, z) ((vec3_t){ x, y, z })

/// Mutate-adds two vectors.
#define vec3_addm(v1, v2) do { \
    (v1).x += (v2).x; \
    (v1).y += (v2).y; \
    (v1).z += (v2).z; \
} while (0)

/// Mutate-subtracts two vectors.
#define vec3_subm(v1, v2) do { \
    (v1).x -= (v2).x; \
    (v1).y -= (v2).y; \
    (v1).z -= (v2).z; \
} while (0)

/// Mutate-multiplies a vector by a scalar.
#define vec3_mulm(v1, a) do { \
    (v1).x *= a; \
    (v1).y *= a; \
    (v1).z *= a; \
} while (0)

/// Mutate-divides a vector by a scalar.
#define vec3_divm(v1, a) do { \
    (v1).x /= a; \
    (v1).y /= a; \
    (v1).z /= a; \
} while (0)

/// Mutate-multiplies two vectors component-wise.
#define vec3_vmulm(v1, v2) do { \
    (v1).x *= (v2).x; \
    (v1).y *= (v2).y; \
    (v1).z *= (v2).z; \
} while (0)

/// Mutate-divides two vectors component-wise.
#define vec3_vdivm(v1, v2) do { \
    (v1).x /= (v2).x; \
    (v1).y /= (v2).y; \
    (v1).z /= (v2).z; \
} while (0)

/// Computes the dot product between two vectors.
#define vec3_dot(v1, v2) ((v1).x * (v2).x + (v1).y * (v2).y + (v1).x * (v2).y)

/// Computes the magnitude of a vector.
#define vec3_mag(v) (sqrt(vec3_dot(v, v)))

/// Normalizes the given vector.
#define vec3_normm(v) vec3_divm(v, vec3_mag(v))

/// Returns a linear combination of three vectors.
vec3_t vec3_comb(scalar_t a, vec3_t v1, scalar_t b, vec3_t v2, scalar_t c, vec3_t v3);
