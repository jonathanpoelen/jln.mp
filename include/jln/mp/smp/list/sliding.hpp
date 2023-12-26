// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/sliding.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class F, bool>
  struct smp_sliding_with_c;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ size, int_ stride = 1, class F = listify, class C = listify>
  using strided_sliding_with_c = typename detail::smp_sliding_with_c<
    subcontract<F>, detail::sliding_stride(size, stride) != -1
  >::template f<size, stride, C>;

  template<int_ size, class F = listify, class C = listify>
  using sliding_with_c = typename detail::smp_sliding_with_c<
    subcontract<F>, (size > 0)
  >::template f<size, 1, C>;

  template<int_ size, int_ stride = 1, class C = listify>
  using strided_sliding_c = typename detail::smp_sliding_with_c<
    mp::listify, detail::sliding_stride(size, stride) != -1
  >::template f<size, stride, C>;

  template<int_ size, class C = listify>
  using sliding_c = typename detail::smp_sliding_with_c<
    mp::listify, (size > 0)
  >::template f<size, 1, C>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(strided_sliding_with, (size), (stride, number<1>), (F, smp::listify), (C, smp::listify),
  smp::strided_sliding_with_c<size::value, stride::value, F, C>)

namespace jln::mp::smp
{
  template<class size, class F = listify, class C = listify>
  using sliding_with = strided_sliding_with<size, number<1>, F, C>;

  template<class size, class stride = number<1>, class C = listify>
  using strided_sliding = strided_sliding_with<size, stride, smp::listify, C>;

  template<class size, class C = listify>
  using sliding = strided_sliding_with<size, number<1>, smp::listify, C>;
}

/// \cond
#include <jln/mp/functional/monadic.hpp>
namespace jln::mp::detail
{
  template<class C>
  using smp_sliding_0 = contract<sliding_0<assume_lists<C>>>;


  template<template<class> class sfinae, int_ size, int_ stride, class F, class C>
  struct _sfinae<sfinae, sliding_<size, stride, F, C>>
  {
    using type = smp::strided_sliding_with_c<size, stride, sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, sliding_0<C>>
  {
    using type = smp_sliding_0<sfinae<C>>;
  };


  template<class F>
  struct smp_sliding_with_c<F, true>
  {
    template<int_ size, int_ stride, class C>
    using f = contract<strided_sliding_with_c<size, stride, F, monadic_xs<subcontract<C>>>>;
  };

  template<>
  struct smp_sliding_with_c<listify, true>
  {
    template<int_ size, int_ stride, class C>
    using f = contract<strided_sliding_with_c<size, stride, listify, assume_lists<C>>>;
  };

  template<>
  struct smp_sliding_with_c<listify, false>
  {
    template<int_ size, int_ stride, class C>
    using f = contract<sliding_0<assume_lists<C>>>;
  };

  template<class F>
  struct smp_sliding_with_c<F, false>
    : smp_sliding_with_c<listify, false>
  {};
}
/// \endcond
