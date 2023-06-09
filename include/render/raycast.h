// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include "linalg/matrix.h"
#include "model/mesh.h"
#include "render/camera.h"
#include "render/frame_buffer.h"

void raycast(frame_buffer_t* frame, const camera3_t* camera, const mesh3_t meshes[], size_t mesh_count);
