// Copyright (C) 2023 Ethan Uppal. All rights reserved.

#include <stdlib.h>
#include "common/common.h"

// Not meant to be efficient
// Meant to work

face3_t cube_geometry[] = {
    face3(0, 1, 2),
    face3(1, 2, 3),

    face3(0, 2, 4),
    face3(2, 4, 6),

    face3(2, 3, 6),
    face3(3, 6, 7),

    face3(4, 5, 6),
    face3(5, 6, 7),

    face3(1, 5, 7),
    face3(1, 3, 7),

    face3(0, 1, 4),
    face3(1, 4, 5),
};

common_t* common_cube(v3_t a, v3_t b, color_t face_colors[CUBE_FACES]) {
    v3_t* cube_vertices = malloc(sizeof(*cube_vertices) * CUBE_VERTICES);
    cube_vertices[0] = v3(a[0], a[1], a[2]); // 0 Bottom Left Near
    cube_vertices[1] = v3(b[0], a[1], a[2]); // 1 Bottom Right Near
    cube_vertices[2] = v3(a[0], b[1], a[2]); // 2 Top Left Near
    cube_vertices[3] = v3(b[0], b[1], a[2]); // 3 Top Right Near
    cube_vertices[4] = v3(a[0], a[1], b[2]); // 4 Bottom Left Far
    cube_vertices[5] = v3(b[0], a[1], b[2]); // 5 Bottom Right Far
    cube_vertices[6] = v3(a[0], b[1], b[2]); // 6 Top Left Far
    cube_vertices[7] = v3(b[0], b[1], b[2]); // 7 Top Right Far

    color_t* colors = malloc(sizeof(*colors) * CUBE_FACES * 2);
    for (size_t i = 0; i < 2 * CUBE_FACES; i++) {
        colors[i] = face_colors[i / 2];
    }
    texture_t* texture = malloc(sizeof(*texture));
    *texture = mono_faces_texture(colors);

    common_t* cube = malloc(sizeof(*cube));
    cube->type = COMMON_TYPE_CUBE;

    // Vertices
    cube->mesh.vertex_count   = CUBE_VERTICES;
    cube->mesh.vertex_list    = cube_vertices;

    // Faces
    cube->mesh.face_count     = lengthof(cube_geometry);
    cube->mesh.face_list      = cube_geometry;

    // Texturing
    cube->mesh.texture        = texture;
    return cube;
}

face3_t rect_geometry[] = {
    face3(0, 1, 2),
    face3(1, 2, 3),
};

common_t* common_rect(v3_t a, v3_t b, v3_t c, v3_t d, color_t color) {
    common_t* rect = malloc(sizeof(*rect));
    rect->type = COMMON_TYPE_RECT;

    v3_t* vertices = malloc(sizeof(*vertices) * RECT_VERTICES);
    vertices[0] = a;
    vertices[1] = b;
    vertices[2] = c;
    vertices[3] = d;

    texture_t* texture = malloc(sizeof(*texture));
    *texture = mono_texture(color);

    rect->mesh.vertex_count   = RECT_VERTICES;
    rect->mesh.vertex_list    = vertices;
    rect->mesh.face_count     = lengthof(rect_geometry);
    rect->mesh.face_list      = rect_geometry;
    rect->mesh.texture        = texture;

    return rect;
}

void common_free(common_t* com) {
    switch (com->type) {
        case COMMON_TYPE_CUBE: {
            free(com->mesh.vertex_list);
            free(com->mesh.texture);
            free(com->mesh.texture->content.mono_faces);
            break;
        }
        case COMMON_TYPE_RECT: {
            free(com->mesh.vertex_list);
            free(com->mesh.texture);
            break;
        }
    }
    free(com);
}
