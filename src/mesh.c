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
    abort("mesh3_transform is not implemented");
}
