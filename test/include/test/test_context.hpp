#pragma once

#include "./is_invocable.hpp"
#include "./is_same.hpp"
#include "jln/mp/functional/call.hpp"
#include "jln/mp/functional/sfinaefwd.hpp"
#include "jln/mp/utility/always.hpp"
#include "jln/mp/smp/utility/unpack.hpp"

namespace
{
namespace ut
{
  using jln::mp::detail::sfinae;

  template<class Mp, class Smp>
  struct test_context
  {
    static_assert((same<Smp, sfinae<Mp>>(), 1));
    static_assert((same<Smp, sfinae<Smp>>(), 1));

    template<class R, class... xs>
    static test_context test()
    {
      invocable<Smp, xs...>();
      invoke_r<R, Mp, xs...>();
      invoke_r<R, Smp, xs...>();
      return {};
    }

    template<class... xs>
    static test_context not_invocable()
    {
      ut::not_invocable<Smp, xs...>();
      return {};
    }
  };

  template<class Mp>
  struct test_context<Mp, void>
  {
    template<class R, class... xs>
    static test_context test()
    {
      invoke_r<R, Mp, xs...>();
      return {};
    }

    template<class... xs>
    static test_context not_invocable()
    {
      ut::not_invocable<Mp, xs...>();
      return {};
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
    static test_pack test_unary()
    {
      static_assert(((void)Tpl<Args..., xs..., unary>{}, 1));
      static_assert(((void)Tpl<Args..., xs..., listify>{}, 1));
      return {};
    }

    template<class... xs>
    static test_pack test_binary()
    {
      static_assert(((void)Tpl<Args..., xs..., binary>{}, 1));
      static_assert(((void)Tpl<Args..., xs..., listify>{}, 1));
      return {};
    }
  };
}

using ut::test_context;
using ut::test_pack;

}
