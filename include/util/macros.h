// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

/// Gives the number of elements in a static array.
#define lengthof(arr) (sizeof(arr)/sizeof(*(arr)))

#define GENERIC_CONSTRUCTOR(T, ...) ((T){ __VA_ARGS__ })
