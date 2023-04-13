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

// https://stackoverflow.com/questions/8381293/how-do-i-force-gcc-to-inline-a-function
#ifndef INLINE
    #ifdef __GNUC__
    #define INLINE __attribute__((always_inline))
    #elif _MSC_VER
    #define INLINE __forceinline
    #else
    #define INLINE inline // I tried :(
    #endif
#endif

#define __eval(...) __VA_ARGS__
#define __eval1(...) __eval(__eval(__VA_ARGS__))
#define __eval2(...) __eval1(__eval1(__VA_ARGS__))
#define __eval3(...) __eval2(__eval2(__VA_ARGS__))
#define __eval4(...) __eval3(__eval3(__VA_ARGS__))
#define __eval5(...) __eval4(__eval4(__VA_ARGS__))
#define __eval6(...) __eval5(__eval5(__VA_ARGS__))
#define eval(...) __eval6(__eval6(__VA_ARGS__))
