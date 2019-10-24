#pragma once

#include "./is_invocable.hpp"
#include "./is_same.hpp"
#include "jln/mp/functional/call.hpp"
#include "jln/mp/functional/always.hpp"
#include "jln/mp/functional/sfinae.hpp"

namespace
{
inline namespace TU
{
  using namespace jln::mp;

  template<class Mp, class Smp>
  struct test_context
  {
    IS_SAME(Smp, sfinae<Mp>);
    IS_SAME(Smp, sfinae<Smp>);

    template<class R, class... xs>
    test_context& test()
    {
      IS_INVOCABLE(Smp, xs...);
      INVOKE_IS_SAME(R, Mp, xs...);
      INVOKE_IS_SAME(R, Smp, xs...);
      return *this;
    }

    template<class... xs>
    test_context& not_invocable()
    {
      not IS_INVOCABLE(Smp, xs...);
      return *this;
    }
  };


  using unary = identity;
  struct binary
  {
    template<class a, class b> using f = void;
  };

  template<template<class...> class Tpl, class... Args>
  struct test_pack
  {
    template<class... xs>
    test_pack& test_unary()
    {
      static_assert((void(Tpl<Args..., unary>{}), 1));
      static_assert((void(Tpl<Args..., listify>{}), 1));
      return *this;
    }

    template<class... xs>
    test_pack& test_binary()
    {
      static_assert((void(Tpl<Args..., binary>{}), 1));
      static_assert((void(Tpl<Args..., listify>{}), 1));
      return *this;
    }
  };
}
}
