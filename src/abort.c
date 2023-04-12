// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include <stdio.h> // fprintf, stderr
#include <stdlib.h> // exit
#include "util/abort.h"

void __abort(const char* msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}
