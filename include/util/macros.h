// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#include <stdio.h>

struct __dump_arg {
    const char* name;
    void** ptr;
    const char* printf;
};

/// Gives the number of elements in a static array.
#define lengthof(arr) (sizeof(arr)/sizeof(*(arr)))

#define GENERIC_CONSTRUCTOR(T, ...) ((T){ __VA_ARGS__ })

#define _(x, fmt) { #x, &_.x, fmt }
#define __dump(v, T, ...) do { \
    T _ = (v); \
    struct __dump_arg dump_args[] = { __VA_ARGS__ }; \
    printf("%s = (%s){", #v, #T); \
    for (size_t i = 0; i < lengthof(dump_args); i++) { \
        if (i == 0) { \
            printf("\n"); \
        } \
        printf("  .%s = ", dump_args[i].name); \
        printf(dump_args[i].printf, *(dump_args[i].ptr)); \
        printf("\n"); \
    } \
    printf("}\n"); \
} while (0)
