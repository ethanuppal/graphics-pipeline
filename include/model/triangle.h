// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include "model/vector.h"

/// Represents a triangle in 3d Euclidean space.
typedef struct {
    v3_t a;
    v3_t b;
    v3_t c;
} tri3_t;
