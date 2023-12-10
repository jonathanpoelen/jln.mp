// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/batched.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class F>
  struct smp_batched_with_c;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ size, class C = listify>
  using batched_c = contract<mp::batched_with_c<size, mp::listify, assume_lists<C>>>;

  template<int_ size, class F = listify, class C = listify>
  using batched_with_c = typename detail::smp_batched_with_c<subcontract<F>>::template f<size, C>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(batched, (Size), (C, smp::listify), smp::batched_c<Size::value, C>)
JLN_MP_MAKE_REGULAR_SMP3_P(batched_with, (Size), (F, smp::listify), (C, smp::listify),
  typename detail::smp_batched_with_c<subcontract<F>>::template f<Size::value, C>)


/// \cond
#include <jln/mp/functional/monadic.hpp>

namespace jln::mp::detail
{
  template<template<class> class sfinae, int_ size, class F, class C>
  struct _sfinae<sfinae, batched_with_c<size, F, C>>
  {
    using type = smp::batched_with_c<size, sfinae<F>, sfinae<C>>;
  };


  template<class F>
  struct smp_batched_with_c
  {
    template<int_ size, class C>
    using f = contract<mp::batched_with_c<size, F, mp::monadic_xs<subcontract<C>>>>;
  };

  template<>
  struct smp_batched_with_c<listify>
  {
    template<int_ size, class C>
    using f = contract<mp::batched_with_c<size, listify, assume_lists<C>>>;
  };
}
/// \endcond
