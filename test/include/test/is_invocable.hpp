#pragma once

#include "jln/mp/number/number.hpp"
#include "jln/mp/functional/is_invocable.hpp"

namespace
{
  namespace Private_TU
  {
    template<class F, class... xs>
    constexpr bool is_invocable()
    {
      jln::mp::true_ x = jln::mp::emp::is_invocable<F, xs...>{};
      (void)x;
      return true;
    }

    template<class F, class... xs>
    constexpr bool is_not_invocable()
    {
      jln::mp::false_ x = jln::mp::emp::is_invocable<F, xs...>{};
      (void)x;
      return true;
    }
  }
}

#define IS_INVOCABLE(...) \
  static_assert(::Private_TU::is_invocable<__VA_ARGS__>())

#define IS_INVOCABLE_V(...) [](auto... _xs) {                    \
  static_assert(::Private_TU::is_invocable<decltype(_xs)...>()); \
}(__VA_ARGS__)

#define IS_NOT_INVOCABLE(...) \
  static_assert(::Private_TU::is_not_invocable<__VA_ARGS__>())

#define IS_NOT_INVOCABLE_V(...) [](auto... _xs) {                    \
  static_assert(::Private_TU::is_not_invocable<decltype(_xs)...>()); \
}(__VA_ARGS__)
