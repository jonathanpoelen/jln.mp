#pragma once

#include "./is_invocable.hpp"
#include "./is_same.hpp"
#include "jln/mp/functional/call.hpp"
#include "jln/mp/functional/lift.hpp"
#include "jln/mp/utility/always.hpp"
#include "jln/mp/smp/utility/unpack.hpp"
#include "jln/mp/smp/utility/conditional.hpp"
#include "jln/mp/smp/functional/sfinaefwd.hpp"

namespace ut
{
  using jln::mp::detail::sfinae;

  template<class...>
  struct other_list
  {};

  using other_listify = jln::mp::lift<other_list>;

  namespace detail
  {
    template<bool, class SfinaeMp, class Smp>
    struct same_smp : jln::mp::true_
    {
      static_assert((same<Smp, SfinaeMp>(), 1));
    };

    template<class SfinaeMp, class Smp>
    struct same_smp<false, SfinaeMp, Smp> : jln::mp::true_
    {
      static_assert((not_same<Smp, SfinaeMp>(), 1));
    };

    template<bool, class Mp>
    struct maybe_sfinae
    {
      using type = sfinae<Mp>;
    };

    template<class Mp>
    struct maybe_sfinae<false, Mp>
    {
      using type = void;
    };
  }

  // 1: check Smp == sfinae<Mp>
  // 0: check Smp != sfinae<Mp>
  // -1: not sfinae<Mp>
  template<class Mp, class Smp, int VerifySfinae = 1>
  struct test_context
  {
    static_assert(detail::same_smp<(VerifySfinae > 0), typename detail::maybe_sfinae<(VerifySfinae >= 0), Mp>::type, Smp>::value);
    static_assert((same<Smp, sfinae<Smp>>(), 1));

    template<class R, class... xs>
    static test_context test()
    {
      invocable<Smp, xs...>();
      invoke_r<R, Mp, xs...>();
      invoke_r<R, Smp, xs...>();
      if constexpr (!VerifySfinae) {
        invoke_r<R, sfinae<Mp>, xs...>();
      }
      return {};
    }

    template<class... xs>
    static test_context not_invocable()
    {
      ut::not_invocable<Smp, xs...>();
      if constexpr (!VerifySfinae) {
        ut::not_invocable<sfinae<Mp>, xs...>();
      }
      return {};
    }
  };

  template<class Mp, int _>
  struct test_context<Mp, void, _>
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

  struct variadic
  {
    template<class... xs>
    using f = jln::mp::list<typename jln::mp::if_<xs, void, void>::type...>;
  };

  // TODO use test_pack2
  template<template<class...> class Tpl, class... Args>
  void test_pack3()
  {
    using jln::mp::lift;
    using jln::mp::call;
    using jln::mp::is_invocable;

    static_assert(((void)call<is_invocable<lift<Tpl>>, Args..., void>::value,1));
    static_assert(((void)call<is_invocable<lift<Tpl>>, Args..., unary>::value,1));
    static_assert(((void)call<is_invocable<lift<Tpl>>, Args..., binary>::value,1));
    static_assert(((void)call<is_invocable<lift<Tpl>>, Args..., listify>::value,1));
    static_assert(((void)call<is_invocable<lift<Tpl>>, Args..., variadic>::value,1));
  }

  template<template<class...> class Tpl, class... Args>
  void test_pack2()
  {
    static_assert(((void)Tpl<Args..., void>{}, 1));
    static_assert(((void)Tpl<Args..., unary>{}, 1));
    static_assert(((void)Tpl<Args..., binary>{}, 1));
    static_assert(((void)Tpl<Args..., listify>{}, 1));
    static_assert(((void)Tpl<Args..., variadic>{}, 1));
    test_pack3<Tpl, Args...>();
  }

  class bad_function {};

  // TODO use test_pack2/3
  template<template<class...> class Tpl, class... Args>
  struct test_pack
  {
    template<class... xs>
    static test_pack test_unary()
    {
      static_assert(((void)Tpl<Args..., xs..., unary>{}, 1));
      static_assert(((void)Tpl<Args..., xs..., listify>{}, 1));
      static_assert(((void)Tpl<Args..., xs..., variadic>{}, 1));
      return {};
    }

    template<class... xs>
    static test_pack test_binary()
    {
      static_assert(((void)Tpl<Args..., xs..., binary>{}, 1));
      static_assert(((void)Tpl<Args..., xs..., listify>{}, 1));
      static_assert(((void)Tpl<Args..., xs..., variadic>{}, 1));
      return {};
    }

    template<class... xs>
    static test_pack test_variadic()
    {
      static_assert(((void)Tpl<Args..., xs..., listify>{}, 1));
      static_assert(((void)Tpl<Args..., xs..., variadic>{}, 1));
      return {};
    }
  };
}

using ut::test_context;
using ut::test_pack;
using ut::test_pack2;
using ut::test_pack3;
using ut::bad_function;

namespace jln::mp::detail
{
  template<template<class> class sfinae>
  struct _sfinae<sfinae, lift<ut::other_list>>
  {
    using type = contract<lift<ut::other_list>>;
  };
}
