// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/split.hpp>
#include <jln/mp/algorithm/split_keep_separator.hpp>

/// \cond
namespace jln::mp::detail
{
#if JLN_MP_GCC
#  define JLN_MP_SMP_SPLIT_KEEP_SEP mp::split_keep_separator_if_with
#else
#  define JLN_MP_SMP_SPLIT_KEEP_SEP detail::smp_split_keep_separator_if_with

  template<class Pred, class F, class C>
  struct smp_split_keep_separator_if_with;
#endif
}
/// \endcond

namespace jln::mp::smp
{
  template<class Pred, class F = listify, class C = listify>
  using split_keep_separator_if_with = typename detail::smp_split_contract<assume_unary<Pred>>
    ::template f<JLN_MP_SMP_SPLIT_KEEP_SEP<
      assume_unary<Pred>, subcontract<F>,
      typename detail::smp_split_continuation<subcontract<F>>::template f<C>
    >>;

  template<class x, class F = listify, class C = listify>
  using split_keep_separator_with = contract<JLN_MP_SMP_SPLIT_KEEP_SEP<
    mp::is<x>, subcontract<F>,
    typename detail::smp_split_continuation<subcontract<F>>::template f<C>
  >>;

  template<class Pred, class C = listify>
  using split_keep_separator_if = typename detail::smp_split_contract<assume_unary<Pred>>
    ::template f<JLN_MP_SMP_SPLIT_KEEP_SEP<assume_unary<Pred>, mp::listify, assume_lists<C>>>;

  template<class x, class C = listify>
  using split_keep_separator = contract<
    JLN_MP_SMP_SPLIT_KEEP_SEP<mp::is<x>, mp::listify, assume_lists<C>>>;
}

/// \cond
#undef JLN_MP_SMP_SPLIT_KEEP_SEP

namespace jln::mp::detail
{
#if !JLN_MP_GCC
  struct smp_split_keep_separator_impl
  {
    template<class Pred, class... xs>
    using f = detail::array_int2_index_dispatcher<
      detail::mk_split_keep_separator_indexes<JLN_MP_RAW_EXPR_TO_BOOL(
        Pred::template f<xs>::value
      )...>
    >;
  };

  template<bool>
  struct smp_split_keep_separator_select
    : smp_split_keep_separator_impl
  {};

  template<class Pred, class F, class C>
  struct smp_split_keep_separator_if_with
  {
    template<class... xs>
    using f = typename smp_split_keep_separator_select<!sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(Pred), xs...>
      ::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };
#endif


  template<template<class> class sfinae, class Pred, class F, class C>
  struct _sfinae<sfinae, split_keep_separator_if_with<Pred, F, C>>
  {
    using type = smp::split_keep_separator_if_with<sfinae<Pred>, sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
