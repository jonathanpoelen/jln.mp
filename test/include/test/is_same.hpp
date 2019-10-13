#pragma once

#define IS_SAME(x, ...) static_assert((void(x() = __VA_ARGS__()), 1))
