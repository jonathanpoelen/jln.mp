#pragma once

#include "jln/mp/functional/call.hpp"

template<class T> struct Result {};

namespace
{
  namespace Private_TU
  {
    template<class T, class U>
    constexpr bool is_same()
    {
      Result<T> x = Result<U>();
      (void)x;
      return true;
    }

    template<class R, class C, class... xs>
    constexpr bool is_same_invoke()
    {
      Result<R> x = Result<jln::mp::call<C, xs...>>();
      (void)x;
      return true;
    }
  }
}

#define IS_SAME(x, ...) static_assert(\
  Private_TU::is_same<x, __VA_ARGS__>())
#define IS_SAME_V(x, ...) static_assert(\
  Private_TU::is_same<decltype(x), __VA_ARGS__>())

#define INVOKE_IS_SAME(R, ...) static_assert(\
  Private_TU::is_same_invoke<R, __VA_ARGS__>())
