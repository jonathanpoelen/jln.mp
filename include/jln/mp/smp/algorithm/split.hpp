// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/smp_listify_or_monadic_xs.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/algorithm/split.hpp>

/// \cond
namespace jln::mp::detail
{
#if JLN_MP_GCC
#  define JLN_MP_SMP_SPLIT mp::split_if_with
#else
#  define JLN_MP_SMP_SPLIT detail::smp_split_if_with

  template<class Pred, class F, class C>
  struct smp_split_if_with;
#endif

  template<class Pred>
  struct smp_split_contract;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Pred, class F = listify, class C = listify>
  using split_if_with = typename detail::smp_split_contract<assume_unary<Pred>>
    ::template f<JLN_MP_SMP_SPLIT<
      assume_unary<Pred>,
      subcontract<F>,
      typename detail::smp_listify_or_monadic_xs<F>::template f<C>
    >>;

  template<class x, class F = listify, class C = listify>
  using split_with = contract<JLN_MP_SMP_SPLIT<
    mp::is<x>, subcontract<F>,
    typename detail::smp_listify_or_monadic_xs<F>::template f<C>
  >>;

  template<class Pred, class C = listify>
  using split_if = typename detail::smp_split_contract<assume_unary<Pred>>
    ::template f<JLN_MP_SMP_SPLIT<assume_unary<Pred>, mp::listify, assume_lists<C>>>;

  template<class x, class C = listify>
  using split = contract<JLN_MP_SMP_SPLIT<mp::is<x>, mp::listify, assume_lists<C>>>;
}


/// \cond
#undef JLN_MP_SMP_SPLIT

#include <jln/mp/functional/monadic.hpp>

namespace jln::mp::detail
{
#if !JLN_MP_GCC
  struct smp_split_impl
  {
    template<class Pred, class... xs>
    using f = detail::array_int2_index_dispatcher<
      detail::mk_split_indices<JLN_MP_RAW_EXPR_TO_BOOL(
        Pred::template f<xs>::value
      )...>
    >;
  };

  template<bool>
  struct smp_split_select
    : smp_split_impl
  {};

  template<class Pred, class F, class C>
  struct smp_split_if_with
  {
    template<class... xs>
    using f = typename smp_split_select<JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs))>
      ::template f<JLN_MP_TRACE_F(Pred), xs...>
      ::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };
#endif


  template<class Pred>
  struct smp_split_contract
  {
    template<class F>
    using f = try_contract<F>;
  };

  template<class T>
  struct smp_split_contract<is<T>>
  {
    template<class F>
    using f = contract<F>;
  };


  template<template<class> class sfinae, class Pred, class F, class C>
  struct _sfinae<sfinae, split_if_with<Pred, F, C>>
  {
    using type = smp::split_if_with<sfinae<Pred>, sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
