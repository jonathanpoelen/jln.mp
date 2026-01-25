// SPDX-FileCopyrightText: 2026 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/drop_front.hpp>

/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct mk_drop_front;

  template<bool>
  struct mk_drop_front_max;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_t n, class C = listify>
  using drop_front_c = typename detail::mk_drop_front<n >= 0 && n <= ~0u>
    ::template f<n, C>;

  template<int_t n, class C = listify>
  using drop_front_max_c = typename detail::mk_drop_front_max<n >= 0 && n <= ~0u>
    ::template f<n, C>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(drop_front, (N), (C, smp::listify), smp::drop_front_c<N::value, C>)
JLN_MP_MAKE_REGULAR_SMP2_P(drop_front_max, (N), (C, smp::listify), smp::drop_front_max_c<N::value, C>)


#include <jln/mp/smp/list/drop_back.hpp>
#include <jln/mp/smp/list/front.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class C>
  struct mk_drop_front_or_at
  {
    template<int_t n>
    using f = test_contract<
      mp::size<mp::greater_equal_than_c<n>>,
      mp::drop_front_c<n, subcontract<C>>
    >;
  };

  template<class C>
  struct mk_drop_front_or_at<try_contract<mp::front<C>>>
  {
    template<int_t n>
    using f = test_contract<
      mp::size<mp::greater_than_c<n>>,
      mp::drop_front_c<n, front<C>>
    >;
  };

  template<>
  struct mk_drop_front<true>
  {
    template<int_t n, class C>
    using f = typename mk_drop_front_or_at<C>::template f<n>;
  };

  template<>
  struct mk_drop_front<false>
    : mk_drop_back<false>
  {};

  template<>
  struct mk_drop_front_max<true>
  {
    template<int_t n, class C>
    using f = contract<mp::drop_front_max_c<n, subcontract<C>>>;
  };

  template<>
  struct mk_drop_front_max<false>
    : mk_drop_back<false>
  {};


  template<template<class> class sfinae, unsigned N, class C>
  struct _sfinae<sfinae, drop_front_c<N, C>>
  {
    using type = mk_drop_front<true>::f<N, sfinae<C>>;
  };

  template<template<class> class sfinae, unsigned N, class C>
  struct _sfinae<sfinae, drop_front_max_c<N, C>>
  {
    using type = mk_drop_front_max<true>::f<N, sfinae<C>>;
  };
}
/// \endcond
