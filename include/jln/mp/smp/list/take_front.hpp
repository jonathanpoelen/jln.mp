// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/take_front.hpp>

/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct mk_take_front;

  template<bool>
  struct mk_take_front_max;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using take_front_c = typename detail::mk_take_front<n >= 0>
    ::template f<n, C>;

  template<int_ n, class C = listify>
  using take_front_max_c = typename detail::mk_take_front_max<n >= 0>
    ::template f<n, C>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(take_front, (N), (C, smp::listify), smp::take_front_c<N::value, C>)
JLN_MP_MAKE_REGULAR_SMP2_P(take_front_max, (N), (C, smp::listify), smp::take_front_max_c<N::value, C>)


#include <jln/mp/number/operators.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, unsigned N, class C>
  struct _sfinae<sfinae, take_front_c<N, C>>
  {
    using type = smp::take_front_c<N, sfinae<C>>;
  };

  template<template<class> class sfinae, unsigned N, class C>
  struct _sfinae<sfinae, take_front_max_c<N, C>>
  {
    using type = smp::take_front_max_c<N, sfinae<C>>;
  };

  template<>
  struct mk_take_front<true>
  {
    template<int_ n, class C>
    using f = test_contract<
      mp::size<mp::greater_equal_than_c<n>>,
      mp::take_front_c<n, subcontract<C>>>;
  };

  template<>
  struct mk_take_front<false>
  {
    template<int_ i, int_ start, class C>
    using f = bad_contract;
  };

  template<>
  struct mk_take_front_max<true>
  {
    template<int_ n, class C>
    using f = contract<mp::take_front_max_c<n, subcontract<C>>>;
  };

  template<>
  struct mk_take_front_max<false>
  {
    template<int_ i, int_ start, class C>
    using f = bad_contract;
  };
}
/// \endcond
