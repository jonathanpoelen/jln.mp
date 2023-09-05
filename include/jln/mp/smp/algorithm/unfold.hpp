// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/functional/recursively.hpp>
#include <jln/mp/algorithm/unfold.hpp>
#include <jln/mp/functional/monadic.hpp>


/// \cond
namespace jln::mp::detail
{
  template<class F>
  struct smp_unfold_impl;
}
/// \endcond

namespace jln::mp::smp
{
  template<class F, class C = listify>
  using unfold = test_contract<
    mp::size<mp::is<mp::number<1>>>,
    mp::recursively<
      detail::smp_unfold_impl<try_subcontract<F>>,
      monadic0<mp::pop_front<subcontract<C>>>
    >
  >;

  using None = contract<mp::None>;
  using Some = contract<mp::listify>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, unfold<F, C>>
  {
    using type = smp::unfold<sfinae<F>, sfinae<C>>;
  };

  template<class>
  struct smp_unfold_next
  {
    template<class... xs>
    using f = _recursion_result<na, na>;
  };

  template<>
  struct smp_unfold_next<None>
  {
    template<class... xs>
    using f = stop_recursion;
  };

  template<class x, class next>
  struct smp_unfold_next<list<x, next>>
  {
    template<class... xs>
    using f = _next_recursion<next, xs..., x>;
  };

  template<class F>
  struct smp_unfold_impl
  {
    template<class state, class... xs>
    using f = typename smp_unfold_next<typename F::template f<state>>::template f<xs...>;
  };
}
/// \endcond
