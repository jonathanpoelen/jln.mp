// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/list/enumerate.hpp>
#include <jln/mp/smp/assume.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class F>
  struct smp_enumerate_select;
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = listify>
  using enumerate = contract<mp::enumerate_with<mp::listify, subcontract<C>>>;

  template<class F = listify, class C = listify>
  using enumerate_with = contract<typename detail::smp_enumerate_select<F>::template f<C>>;
}

/// \cond
namespace jln::mp::detail
{
  template<class F>
  struct smp_enumerate_select
  {
    template<class C>
    using f = enumerate_with<assume_binary<F>, monadic_xs<subcontract<C>>>;
  };

  template<>
  struct smp_enumerate_select<listify>
  {
    template<class C>
    using f = enumerate_with<listify, subcontract<C>>;
  };

  template<>
  struct smp_enumerate_select<smp::listify>
    : smp_enumerate_select<listify>
  {};


  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, enumerate_with<F, C>>
  {
    using type = smp::enumerate_with<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
