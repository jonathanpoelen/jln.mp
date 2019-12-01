#pragma once

#include "jln/mp/functional/call.hpp"

namespace
{
namespace ut
{
  template<class T>
  struct Result
  {};

  template<class T>
  struct Expected
  {
    constexpr Expected(Result<T>)
    {}
  };

  template<class T>
  struct Differ
  {
    Differ(Result<T>) = delete;
    template<class U> constexpr Differ(Result<U>) {}
  };

  template<class T, class U>
  constexpr void same()
  {
    Expected<T> should_be_same = Result<U>();
    (void)should_be_same;
  }

  template<class T, class U>
  constexpr void not_same()
  {
    Differ<T> should_not_be_same = Result<U>();
    (void)should_not_be_same;
  }

  template<class R, class C, class... xs>
  constexpr void invoke_r()
  {
    Expected<R> should_be_same = Result<jln::mp::call<C, xs...>>();
    (void)should_be_same;
  }
}
}
