// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include <stddef.h>
#include "model/triangle.h" // tri3_t
#include "model/space.h" // matrix3_t
#include "util/macros.h" // GENERIC_CONSTRUCTOR

#define MAX_VERTICES 256
typedef size_t vertex_size_t;

/// Represents a face in a face-vertex mesh.
typedef struct {
    vertex_size_t a;
    vertex_size_t b;
    vertex_size_t c;
} face3_t;

/// Represents a face-vertex mesh.
typedef struct {
    vertex_size_t vertex_count;
    vec3_t* vertex_list;

    size_t face_count;
    face3_t* face_list;
} mesh3_t;

#define face3(a, b, c) ((face3_t){ a, b, c })

#define mesh3(...) GENERIC_CONSTRUCTOR(mesh3_t, __VA_ARGS__)

/// Returns the triangle associated with the given face index in the mesh.
tri3_t mesh3_face_tri(const mesh3_t* mesh, size_t i);

/// Applies the given transform to the mesh around the given origin.
void mesh3_transform(mesh3_t* mesh, vec3_t origin, matrix3_t transform);
