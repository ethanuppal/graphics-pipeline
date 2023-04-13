// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include "model/mesh.h"
#include "util/abort.h" // abort

void mesh3_face_load_tri(v3_t tri[3], const mesh3_t* mesh, size_t i) {
    const face3_t face = mesh->face_list[i];

    tri[0] = mesh->vertex_list[face.a];
    tri[1] = mesh->vertex_list[face.b];
    tri[2] = mesh->vertex_list[face.c];
}

void mesh3_transform(mesh3_t* mesh, v3_t origin, matrix3_t transform) {
    for (size_t i = 0; i < mesh->vertex_count; i++) {
        mesh->vertex_list[i] -= origin;
        mesh->vertex_list[i] = vec3_comb(
            mesh->vertex_list[i][0],
            transform.cols[0],
            mesh->vertex_list[i][1],
            transform.cols[1],
            mesh->vertex_list[i][2],
            transform.cols[2]
        );
        mesh->vertex_list[i] += origin;
    }
}
