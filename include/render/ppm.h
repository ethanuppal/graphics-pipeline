// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include <stdio.h> // FILE
#include "render/frame_buffer.h"

int ppm_write_frame(FILE* dest, const frame_buffer_t* frame);
