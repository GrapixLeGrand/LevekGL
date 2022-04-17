#pragma once

#include <stdio.h>
#include <cassert>

#define LEVEKGL_ERROR_HEADER printf("Levek::assert(%s:%d)", __FILE__, __LINE__);
#define LEVEKGL_ASSERT(EXPR, FMT, ...) if (!(EXPR)) { LEVEKGL_ERROR_HEADER printf(FMT, ##__VA_ARGS__); assert(false); } 
 