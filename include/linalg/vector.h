// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include <math.h> // sqrt
#include <smmintrin.h> // SIMD
#include "util/macros.h" // INLINE

typedef float scalar_t;

typedef scalar_t v3_t __attribute__((vector_size (16)));
typedef scalar_t v2_t __attribute__((vector_size (8)));

/// Creates a 3d vector with the given components.
#define vec2(x, y) ((v2_t){ x, y })

/// Creates a 3d vector with the given components.
#define vec3(x, y, z) ((v3_t){ x, y, z })

// /// Mutate-adds two vectors.
// #define vec3_addm(v1, v2) do { \
//     (v1).x += (v2).x; \
//     (v1).y += (v2).y; \
//     (v1).z += (v2).z; \
// } while (0)
//
// /// Mutate-subtracts two vectors.
// #define vec3_subm(v1, v2) do { \
//     (v1).x -= (v2).x; \
//     (v1).y -= (v2).y; \
//     (v1).z -= (v2).z; \
// } while (0)
//
// /// Mutate-multiplies a vector by a scalar.
// #define vec3_mulm(v1, a) do { \
//     (v1).x *= a; \
//     (v1).y *= a; \
//     (v1).z *= a; \
// } while (0)
//
// /// Mutate-divides a vector by a scalar.
// #define vec3_divm(v1, a) do { \
//     (v1).x /= a; \
//     (v1).y /= a; \
//     (v1).z /= a; \
// } while (0)
//
// /// Mutate-multiplies two vectors component-wise.
// #define vec3_vmulm(v1, v2) do { \
//     (v1).x *= (v2).x; \
//     (v1).y *= (v2).y; \
//     (v1).z *= (v2).z; \
// } while (0)
//
// /// Mutate-divides two vectors component-wise.
// #define vec3_vdivm(v1, v2) do { \
//     (v1).x /= (v2).x; \
//     (v1).y /= (v2).y; \
//     (v1).z /= (v2).z; \
// } while (0)

/// Computes the dot product between two vectors.
// #define vec3_dot(v1, v2) ((v1).x * (v2).x + (v1).y * (v2).y + (v1).z * (v2).z)

//#define vec3_dot(v1, v2) eval(V_DOT(v1, v2))
/// Computes the dot product between the two given vectors.
#define V_DOT(x, y) _mm_dp_ps(x, y) // single precision
scalar_t vec3_dot(v3_t v1, v3_t v2);

/// Computes the cross product between the two given vectors.
v3_t vec3_cross(v3_t const vec0, v3_t const vec1);

/// Returns a vector containing the corresponding minimum elements of the given two vectors.
#define vec3_min(v1, v2) _mm_min_ps(v1, v2)

/// Returns a vector containing the corresponding maximum elements of the given two vectors.
#define vec3_max(v1, v2) _mm_max_ps(v1, v2)

/// Returns the minimum element in the vector.
scalar_t vec3_min_e(v3_t v);

/// Returns the maximum element in the vector.
scalar_t vec3_max_e(v3_t v);

/// Computes the triple product of the three given vectors.
#define vec3_triple(v1, v2, v3) vec3_dot(v1, vec3_cross(v2, v3))

/// Computes the magnitude of a vector.
#define vec3_mag(v) (sqrtf(vec3_dot(v, v)))

/// Normalizes the given vector.
#define vec3_normm(v) do { v /= vec3_mag(v); } while (0)

// /// Returns the sum of two vectors.
// vec3_t vec3_add(vec3_t v1, vec3_t v2);
//
// /// Returns the difference of two vectors.
// vec3_t vec3_sub(vec3_t v1, vec3_t v2);

/// Returns a linear combination of three vectors.
#define vec3_comb(a, v1, b, v2, c, v3) ((a) * (v1) + (b) * (v2) + (c) * (v3))

/// Linearly interpolates between the two given vectors.
#define vec3_lerp(v1, v2, t) ((v1) * (1 - (t)) + (v2) * (t))

#define vec3_lerp_vec(v1, v2, vt) ((v1) * (1 - (vt)) + (v2) * (vt))
// void vec3_dump(vec3_t v);
