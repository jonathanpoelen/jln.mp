#pragma once

#include "jln/mp/functional/call.hpp"

namespace
{
namespace ut
{
  template<class T>
  struct Result
  {};

  template<class T, class U>
  constexpr void same()
  {
    Result<T> should_be_same = Result<U>();
    (void)should_be_same;
  }

  template<class R, class C, class... xs>
  constexpr void invoke_r()
  {
    Result<R> should_be_same = Result<jln::mp::call<C, xs...>>();
    (void)should_be_same;
  }
}
}
