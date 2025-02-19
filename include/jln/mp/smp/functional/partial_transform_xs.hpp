// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/partial_transform_xs.hpp>

/// \cond
namespace jln::mp::detail
{
  struct _smp_partial_transform_xs;
  struct _smp_partial_transform_1_xs;
  struct _smp_partial_transform0_xs;
}
/// \endcond

namespace jln::mp::smp
{
  template<class... Fs>
  using partial_transform_xs = typename mp::conditional_c<sizeof...(Fs) == 0>
    ::template f<
      mp::always<bad_contract>,
      JLN_MP_CONDITIONAL_P_C_T(
        (sizeof...(Fs) == 1),
        (detail::_smp_partial_transform_1_xs),
        (rotate_c<-2, detail::_smp_partial_transform_xs>)
      )
    >
    ::template f<Fs...>;

  template<class... Fs>
  using partial_transform0_xs = typename mp::conditional_c<sizeof...(Fs) == 0>
    ::template f<
      mp::always<bad_contract>,
      JLN_MP_CONDITIONAL_P_C_T(
        (sizeof...(Fs) == 1),
        (detail::_smp_partial_transform_1_xs),
        (rotate_c<-1, detail::_smp_partial_transform0_xs>)
      )
    >
    ::template f<Fs...>;
}

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/number/operators.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/list/is_empty.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, partial_transform_xs<Fs...>>
  {
    using type = smp::partial_transform_xs<sfinae<Fs>...>;
  };

  struct _smp_partial_transform_xs
  {
    template<class F, class C, class... Fs>
    using f = test_contract<
      size<greater_equal_than_c<sizeof...(Fs)>>,
      partial_transform_xs<assume_unary<Fs>..., subcontract<F>, monadic_xs<subcontract<C>>>
    >;
  };

  struct _smp_partial_transform_1_xs
  {
    template<class C>
    using f = test_contract<is_empty<>, subcontract<C>>;
  };

  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, partial_transform0_xs<Fs...>>
  {
    using type = smp::partial_transform0_xs<sfinae<Fs>...>;
  };

  struct _smp_partial_transform0_xs
  {
    template<class C, class... Fs>
    using f = contract<mp::partial_transform0_xs<
      subcontract<Fs>..., monadic_xs<subcontract<C>>>>;
  };
}
/// \endcond
