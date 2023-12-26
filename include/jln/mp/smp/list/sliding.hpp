// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/sliding.hpp>

namespace jln::mp::smp
{
  template<int_ size, class C = listify>
  using sliding_c = try_contract<mp::sliding_c<size, assume_lists<C>>>;

  template<int_ size, int_ stride = 1, class C = listify>
  using strided_sliding_c = try_contract<
    mp::strided_sliding_c<size, stride, assume_lists<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(sliding, (size, number<1>), (C, smp::listify),
  smp::sliding_c<size::value, C>)

JLN_MP_MAKE_REGULAR_SMP3_P(strided_sliding, (size), (stride, number<1>), (C, smp::listify),
  smp::strided_sliding_c<size::value, stride::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<class C>
  using smp_sliding_0 = try_contract<call_trace_xs_0<subcontract<C>>>;

  template<template<class> class sfinae, int_ size, int_ stride, class C>
  struct _sfinae<sfinae, sliding_<size, stride, C>>
  {
    using type = smp::strided_sliding_c<size, stride, sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, call_trace_xs_0<C>>
  {
    using type = smp_sliding_0<sfinae<C>>;
  };
}
/// \endcond
