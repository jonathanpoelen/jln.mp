// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include "./is_invocable.hpp"
#include "./is_same.hpp"
#include "jln/mp/list/listify.hpp"
#include "jln/mp/functional/if.hpp"
#include "jln/mp/functional/call.hpp"
#include "jln/mp/functional/continuation.hpp"
#include "jln/mp/smp/functional/sfinaefwd.hpp"

namespace jln::mp
{
  template<class C>
  struct contract;
}

namespace ut
{
  using jln::mp::detail::sfinae;

  class SmpValue;
  class MpToSmpValue;

  namespace detail
  {
    template<bool, class SfinaeMp, class Smp>
    struct same_smp : jln::mp::true_
    {
      static_assert((same<Smp, SfinaeMp, SmpValue, MpToSmpValue>(), 1));
    };

    template<class SfinaeMp, class Smp>
    struct same_smp<false, SfinaeMp, Smp> : jln::mp::true_
    {
      static_assert((not_same<Smp, SfinaeMp, SmpValue, MpToSmpValue>(), 1));
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

  template<class>
  struct is_contract
  {
    static constexpr bool value = false;
  };

  template<class T>
  struct is_contract<::jln::mp::contract<T>>
  {
    static constexpr bool value = true;
  };

  // 1: check Smp == sfinae<Mp>
  // 0: check Smp != sfinae<Mp>
  // -1: not sfinae<Mp>
  template<class Mp, class Smp, int VerifySfinae = 1>
  struct test_context
  {
    static_assert(detail::same_smp<(VerifySfinae > 0), typename detail::maybe_sfinae<(VerifySfinae >= 0), Mp>::type, Smp>::value);
    static_assert((same<Smp, sfinae<Smp>>(), 1));
    static_assert(is_contract<Smp>::value);

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
    template<class a, class b>
    using f = jln::mp::list<a, b>;
  };

  template<template<class...> class Tpl, class... Args>
  void test_unary_pack()
  {
    static_assert(((void)Tpl<Args..., unary>{}, 1));
    static_assert(((void)Tpl<Args..., listify>{}, 1));
  }

  template<template<class...> class Tpl, class... Args>
  void test_binary_pack()
  {
    static_assert(((void)Tpl<Args..., binary>{}, 1));
    static_assert(((void)Tpl<Args..., listify>{}, 1));
  }

  template<template<class...> class Tpl, class... Args>
  void test_mulary_pack()
  {
    static_assert(((void)Tpl<Args..., unary>{}, 1));
    static_assert(((void)Tpl<Args..., binary>{}, 1));
    static_assert(((void)Tpl<Args..., listify>{}, 1));
  }

  class bad_function {};
}

using ut::test_context;
using ut::test_unary_pack;
using ut::test_binary_pack;
using ut::test_mulary_pack;
using ut::bad_function;
