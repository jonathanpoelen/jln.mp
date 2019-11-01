#pragma once

#include "./is_invocable.hpp"
#include "./is_same.hpp"
#include "jln/mp/functional/call.hpp"
#include "jln/mp/functional/sfinaefwd.hpp"
#include "jln/mp/utility/always.hpp"
#include "jln/mp/smp/utility/unpack.hpp"

namespace
{
inline namespace TU
{
  using jln::mp::detail::sfinae;

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
      IS_NOT_INVOCABLE(Smp, xs...);
      return *this;
    }
  };

  template<class Mp>
  struct test_context<Mp, void>
  {
    template<class R, class... xs>
    test_context& test()
    {
      INVOKE_IS_SAME(R, Mp, xs...);
      return *this;
    }

    template<class... xs>
    test_context& is_invocable()
    {
      IS_NOT_INVOCABLE(Mp, xs...);
      return *this;
    }

    template<class... xs>
    test_context& not_invocable()
    {
      IS_NOT_INVOCABLE(Mp, xs...);
      return *this;
    }
  };


  using unary = jln::mp::identity;
  using jln::mp::listify;
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
      static_assert(((void)Tpl<Args..., xs..., unary>{}, 1));
      static_assert(((void)Tpl<Args..., xs..., listify>{}, 1));
      return *this;
    }

    template<class... xs>
    test_pack& test_binary()
    {
      static_assert(((void)Tpl<Args..., xs..., binary>{}, 1));
      static_assert(((void)Tpl<Args..., xs..., listify>{}, 1));
      return *this;
    }
  };
}
}
