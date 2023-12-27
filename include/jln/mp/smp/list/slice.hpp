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
    using f = contract<mp::strided_slice_c<start, count, step, subcontract<C>>>;
  };
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ start, unsigned count, unsigned step = 1, class C = listify>
  using strided_slice_c = typename detail::smp_slice_select<(step > 0 || !count)>
    ::template f<start, count, step, C>;

  template<int_ start, unsigned count, class C = listify>
  using slice_c = typename detail::smp_slice_select<true>
    ::template f<start, count, 1, C>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(strided_slice, (start), (count), (step, number<1>), (C, smp::listify),
  smp::strided_slice_c<start::value, count::value, step::value, C>)

namespace jln::mp::smp
{
  template<class start, class count, class C = listify>
  using slice = smp::strided_slice<start, count, number<1>, C>;
}


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
  struct _sfinae<sfinae, strided_slice_c<start, count, step, C>>
  {
    using type = smp::strided_slice_c<start, count, step, sfinae<C>>;
  };
}
/// \endcond
