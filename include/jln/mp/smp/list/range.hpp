// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/range.hpp>

namespace jln::mp::smp
{
  template<int_t beg, int_t end, class C = listify>
  using range_c = contract<mp::range_c<
    beg, end, subcontract<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(range, (beg), (end), (C, smp::listify),
  smp::range_c<beg::value, end::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, int_t beg, int_t end, class C>
  struct _sfinae<sfinae, range_c<beg, end, C>>
  {
    using type = smp::range_c<beg, end, sfinae<C>>;
  };
}
/// \endcond
