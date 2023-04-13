// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include "model/mesh.h"
#include "util/abort.h" // abort

tri3_t mesh3_face_tri(const mesh3_t* mesh, size_t i) {
    const face3_t face = mesh->face_list[i];

    tri3_t tri;
    tri.a = mesh->vertex_list[face.a];
    tri.b = mesh->vertex_list[face.b];
    tri.c = mesh->vertex_list[face.c];

    return tri;
}

void mesh3_transform(mesh3_t* mesh, vec3_t origin, matrix3_t transform) {
    for (size_t i = 0; i < mesh->vertex_count; i++) {
        vec3_subm(mesh->vertex_list[i], origin);
        mesh->vertex_list[i] = vec3_comb(
            mesh->vertex_list[i].x,
            transform.cols[0],
            mesh->vertex_list[i].y,
            transform.cols[1],
            mesh->vertex_list[i].z,
            transform.cols[2]
        );
        vec3_addm(mesh->vertex_list[i], origin);
    }
}
