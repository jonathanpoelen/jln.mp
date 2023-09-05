// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/slice.hpp>

/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct smp_slice_select;
}
/// \endcond

namespace jln::mp::smp
{
  template<unsigned start, unsigned size, unsigned stride = 1, class C = listify>
  using slice_c = typename detail::smp_slice_select<(stride > 0)>
    ::template f<start, size, stride, C>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(slice, (start), (size), (stride, number<1>), (C, smp::listify),
  smp::slice_c<start::value, size::value, stride::value, C>)


/// \cond
namespace jln::mp::detail
{
  template<>
  struct smp_slice_select<false>
  {
    template<unsigned start, unsigned size, unsigned stride, class C>
    using f = bad_contract;
  };

  template<unsigned start, unsigned size, unsigned stride>
  struct smp_slice_check
  {
    template<class... xs>
    using f = mp::number<start <= sizeof...(xs)
                      && (size - 1) * stride + start + 1 <= sizeof...(xs)>;
  };

  template<>
  struct smp_slice_select<true>
  {
    template<unsigned start, unsigned size, unsigned stride, class C>
    using f = test_contract<
      smp_slice_check<start, size, stride>,
      mp::slice_c<start, size, stride, subcontract<C>>>;
  };

  template<template<class> class sfinae, unsigned start, unsigned size, unsigned stride, class C>
  struct _sfinae<sfinae, slice_c<start, size, stride, C>>
  {
    using type = smp::slice_c<start, size, stride, sfinae<C>>;
  };
}
/// \endcond
