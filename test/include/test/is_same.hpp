#pragma once

template<class T> struct Result {};

#define IS_SAME(x, ...) static_assert((void(Result<x>() = Result<__VA_ARGS__>()), 1))
#define IS_SAME_V(x, ...) static_assert((void(Result<decltype(x)>() = Result<__VA_ARGS__>()), 1))
