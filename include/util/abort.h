// Copyright (C) Ethan Uppal 2023. All rights reserved.
#pragma once

#define abort(...) __abort("abort: " __VA_ARGS__ "")
void __abort(const char* msg);
