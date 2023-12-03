// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/slice.hpp>

/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct smp_slice_select
  {
    template<int_ start, unsigned count, unsigned step, class C>
    using f = contract<mp::slice_with_step_c<start, count, step, subcontract<C>>>;
  };
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ start, unsigned count, unsigned step = 1, class C = listify>
  using slice_with_step_c = typename detail::smp_slice_select<(step > 0)>
    ::template f<start, count, step, C>;

  template<int_ start, unsigned count, class C = listify>
  using slice_c = typename detail::smp_slice_select<true>
    ::template f<start, count, 1, C>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(slice_with_step, (start), (size), (step, number<1>), (C, smp::listify),
  smp::slice_with_step_c<start::value, size::value, step::value, C>)

JLN_MP_MAKE_REGULAR_SMP3_P(slice, (start), (size), (C, smp::listify),
  smp::slice_c<start::value, size::value, C>)


/// \cond
namespace jln::mp::detail
{
  template<>
  struct smp_slice_select<false>
  {
    template<int_ start, unsigned count, unsigned step, class C>
    using f = bad_contract;
  };

  template<template<class> class sfinae, int_ start, unsigned count, unsigned step, class C>
  struct _sfinae<sfinae, slice_with_step_c<start, count, step, C>>
  {
    using type = smp::slice_with_step_c<start, count, step, sfinae<C>>;
  };
}
/// \endcond
