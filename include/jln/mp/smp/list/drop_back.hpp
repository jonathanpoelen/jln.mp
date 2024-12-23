// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/drop_back.hpp>
#include <type_traits> // std::void_t

/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct mk_drop_back;

  template<bool>
  struct mk_drop_back_max;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_t n, class C = listify>
  using drop_back_c = typename detail::mk_drop_back<n >= 0 && n <= ~0u>
    ::template f<n, C>;

  template<int_t n, class C = listify>
  using drop_back_max_c = typename detail::mk_drop_back_max<n >= 0 && n <= ~0u>
    ::template f<n, C>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(drop_back, (N), (C, smp::listify), smp::drop_back_c<N::value, C>)
JLN_MP_MAKE_REGULAR_SMP2_P(drop_back_max, (N), (C, smp::listify), smp::drop_back_max_c<N::value, C>)


#include <jln/mp/number/operators.hpp>
#include <jln/mp/smp/algorithm/repeat.hpp> // mk_repeat<false>

/// \cond
namespace jln::mp::detail
{
  template<>
  struct mk_drop_back<true>
  {
    template<int_t n, class C>
    using f = test_contract<
      mp::size<mp::greater_equal_than_c<n>>,
      mp::drop_back_c<n, subcontract<C>>>;
  };

  template<>
  struct mk_drop_back<false> : mk_repeat<false>
  {};

  template<>
  struct mk_drop_back_max<true>
  {
    template<int_t n, class C>
    using f = contract<mp::drop_back_max_c<n, subcontract<C>>>;
  };

  template<>
  struct mk_drop_back_max<false>
    : mk_drop_back<false>
  {};


  template<template<class> class sfinae, unsigned N, class C>
  struct _sfinae<sfinae, drop_back_c<N, C>>
  {
    using type = mk_drop_back<true>::f<N, sfinae<C>>;
  };

  template<template<class> class sfinae, unsigned N, class C>
  struct _sfinae<sfinae, drop_back_max_c<N, C>>
  {
    using type = mk_drop_back_max<true>::f<N, sfinae<C>>;
  };
}
/// \endcond
