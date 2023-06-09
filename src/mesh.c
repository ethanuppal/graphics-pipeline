// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include <stdlib.h> // malloc, free
#include "model/mesh.h"
#include "linalg/matrix.h"
#include "util/abort.h" // abort
#include "util/macros.h" // INLINE

/// Loads the vertices triangle associated with the given face index in the mesh.
void mesh3_face_load_tri(v3_t tri[VECTORS_PER_TRI], const mesh3_t* mesh, size_t i, aabb_t* aabb);

/// Allocates an array of triangles, each represented by three subsequent vertices.
v3_t* mesh3_generate_triangles(const mesh3_t* mesh, aabb_t* aabb);

void INLINE mesh3_face_load_tri(v3_t tri[VECTORS_PER_TRI], const mesh3_t* mesh, size_t i, aabb_t* aabb) {
    // Extract vertices for face.
    const face3_t face = mesh->face_list[i];
    const v3_t a = mesh->vertex_list[face.a];
    const v3_t b = mesh->vertex_list[face.b];
    const v3_t c = mesh->vertex_list[face.c];

    // Set vectors into triangle buffer.
    tri[0] = a;
    tri[0][3] = (scalar_t)i; // horrible but works
    tri[1] = a - b;
    tri[2] = a - c;

    // Find min and max xyz
    const v3_t min_xyz = vec3_min(a, vec3_min(b, c));
    const v3_t max_xyz = vec3_max(a, vec3_max(b, c));

    // Set aabb bounds to include min and max xyz.
    aabb->p0 = vec3_min(aabb->p0, min_xyz);
    aabb->p1 = vec3_max(aabb->p1, max_xyz);

    // printf("%f %f %f %f %f %f\n", aabb->p0[0], aabb->p0[1], aabb->p0[2], aabb->p1[0], aabb->p1[1], aabb->p1[2]);
}

v3_t* mesh3_generate_triangles(const mesh3_t* mesh, aabb_t* aabb) {
    const size_t tris_length = mesh3_triangles_size(*mesh);
    v3_t* tris = malloc(sizeof(*tris) * tris_length);
    for (size_t i = 0; i < mesh->face_count; i++) {
        mesh3_face_load_tri(tris + i * VECTORS_PER_TRI, mesh, i, aabb);
    }
    return tris;
}

mesh3_internal_t* create_mesh_internals(const mesh3_t meshes[], size_t mesh_count) {
    mesh3_internal_t* mesh_internals = malloc(sizeof(*mesh_internals) * mesh_count);
    for (size_t i = 0; i < mesh_count; i++) {
        const mesh3_t* mesh = &meshes[i];
        mesh3_internal_t* mesh_int = &mesh_internals[i];
        mesh_int->aabb = aabb_maxmin();
        mesh_int->size = mesh3_triangles_size(*mesh);
        mesh_int->triangles = mesh3_generate_triangles(mesh, &mesh_int->aabb);
        mesh_int->texture = mesh->texture;
    }
    return mesh_internals;
}

void free_mesh_internals(mesh3_internal_t* meshes, size_t mesh_count) {
    for (size_t i = 0; i < mesh_count; i++) {
        free(meshes[i].triangles);
    }
    free(meshes);
}

v3_t mesh3_transform(mesh3_t* mesh, v3_t origin, matrix3_t transform) {
    for (size_t i = 0; i < mesh->vertex_count; i++) {
        mesh->vertex_list[i] -= origin;
        mesh->vertex_list[i] = matrix3_apply(transform, mesh->vertex_list[i]);
        mesh->vertex_list[i] += origin;
    }
    return matrix3_apply(transform, origin);
}
