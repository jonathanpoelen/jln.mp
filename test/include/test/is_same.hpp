#pragma once

namespace ut
{
namespace
{
  template<class T>
  struct Result
  {};

  template<class T>
  struct Expected
  {
    constexpr Expected(Result<T>){}
  };

  // template<class T>
  // using Expected = Result<T>;

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
    Expected<R> should_be_same = Result<typename C::template f<xs...>>();
    (void)should_be_same;
  }
}
}
