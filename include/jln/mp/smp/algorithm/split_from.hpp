// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/split_from.hpp>
#include <jln/mp/functional/invoke_twice.hpp>
#include <jln/mp/functional/tee.hpp>
#include <jln/mp/detail/smp_listify_or_monadic_xs.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class SubC1, class SubC2, class C>
  class _smp_split_from;
}
/// \endcond

namespace jln::mp::smp
{
  template<class GetIndex, class SubC1 = listify, class SubC2 = SubC1, class C = listify>
  using split_from2 = contract<mp::invoke_twice<mp::tee<
    subcontract<GetIndex>,
    detail::_smp_split_from<
      subcontract<SubC1>, subcontract<SubC2>,
      typename detail::smp_listify_or_monadic_xs<SubC1, SubC2>::template f<C>
    >
  >>>;

  template<class GetIndex, class C = listify>
  using split_from = contract<mp::invoke_twice<mp::tee<
    subcontract<GetIndex>,
    detail::_smp_split_from<mp::listify, mp::listify, assume_lists<C>>
  >>>;
}


#include <jln/mp/functional/continuation.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/detail/expr_conversion.hpp>

/// \cond
namespace jln::mp::detail
{
  struct smp_split_from_i
  {
    template<class position, class C1, class C2, class C, class... xs>
    using f = typename detail::split_at_with_impl<C, C1, C2,
      typename JLN_MP_CALLER_XS(xs, detail::split_at_impl<position::value>)
      ::template f<position::value, list<>, xs...>
    >::type;
  };

  template<class SubC1, class SubC2, class C>
  class _smp_split_from
  {
    template<class i, class = void>
    struct _impl : always<na>
    {};

    template<class i>
    struct _impl<i, decltype(void(JLN_MP_INTEGRAL_AS(uint_t, i::value)))>
    {
      template<class... xs>
      using f = typename conditional_c<i::value <= sizeof...(xs)>
        ::template f<smp_split_from_i, violation>
        ::template f<i, SubC1, SubC2, C, xs...>;
    };

  public:
    template<class i>
    using f = _impl<i>;
  };


  template<template<class> class sfinae, class GetIndex, class SubC1, class SubC2, class C>
  struct _sfinae<sfinae, split_from2<GetIndex, SubC1, SubC2, C>>
  {
    using type = smp::split_from2<sfinae<GetIndex>, sfinae<SubC1>, sfinae<SubC2>, sfinae<C>>;
  };
}
/// \endcond
