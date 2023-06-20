// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include <stddef.h>
#include "linalg/matrix.h" // matrix3_t
#include "model/texture.h" // texture_t
#include "util/macros.h" // GENERIC_CONSTRUCTOR
#include "model/aabb.h" // aabb_t

// #define MAX_VERTICES 256
typedef size_t vertex_size_t;

#define VECTORS_PER_TRI 3

/// Represents a face in a face-vertex mesh.
typedef struct {
    vertex_size_t a;
    vertex_size_t b;
    vertex_size_t c;
} face3_t;

/// Represents a face-vertex mesh.
typedef struct mesh3_t {
    vertex_size_t vertex_count;
    v3_t* vertex_list;

    size_t face_count;
    face3_t* face_list;

    texture_t* texture;
} mesh3_t;

typedef struct {
    size_t size;
    v4_t* triangles;
    aabb_t aabb;
    texture_t* texture;
} mesh3_internal_t;

#define face3(a, b, c) ((face3_t){ a, b, c })

#define mesh3(...) GENERIC_CONSTRUCTOR(mesh3_t, __VA_ARGS__)

#define mesh3_triangles_size(mesh) ((mesh).face_count * VECTORS_PER_TRI)

mesh3_internal_t* create_mesh_internals(const mesh3_t meshes[], size_t mesh_count);

void free_mesh_internals(mesh3_internal_t* meshes, size_t mesh_count);

/// Applies the given transform to the mesh around the given origin.
v3_t mesh3_transform(mesh3_t* mesh, v3_t origin, matrix3_t transform);
