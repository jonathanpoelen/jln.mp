// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/at.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/smp/number/to_bool.hpp>
#include <jln/mp/functional/invoke_twice.hpp>
#include <jln/mp/functional/if.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class F, bool = true>
  struct smp_if_impl;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Pred, class TC, class FC = always<false_>>
  using if_ = typename detail::smp_if_impl<mp::if_<
    subcontract<Pred>, subcontract<TC>, subcontract<FC>
  >>::type;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, if_<Pred, TC, FC>>
  {
    using type = smp::if_<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };


  // 0 => no change
  // 1 => no change after check
  // 2 => select TC
  // 3 => select FC
  template<class Pred, class Pred2>
  constexpr int smp_if_reduce_tc_v = 0;

  template<class Pred>
  constexpr int smp_if_reduce_tc_v<Pred, Pred> = 2;

  template<class x, class y>
  constexpr int smp_if_reduce_tc_v<size<is<x>>, size<is<y>>> = 3;

  template<class x>
  constexpr int smp_if_reduce_tc_v<size<is<x>>, size<is<x>>> = 2;

  template<int_ i1, int_ i2>
  constexpr int smp_if_reduce_tc_v<size<equal_to_c<i1>>, size<equal_to_c<i2>>>
    = i2 == i1 ? 2 : 3;


  template<int_ i1, int_ i2>
  constexpr int smp_if_reduce_tc_v<size<less_equal_than_c<i1>>, size<less_equal_than_c<i2>>>
    = i1 <= i2 ? 1 : 2;

  template<int_ i1, int_ i2>
  constexpr int smp_if_reduce_tc_v<size<less_equal_than_c<i1>>, size<less_than_c<i2>>>
    = i1 < i2 ? 1 : 2;

  template<int_ i1, int_ i2>
  constexpr int smp_if_reduce_tc_v<size<less_than_c<i1>>, size<less_than_c<i2>>>
    = i1 <= i2 ? 1 : 2;

  template<int_ i1, int_ i2>
  constexpr int smp_if_reduce_tc_v<size<less_than_c<i1>>, size<less_equal_than_c<i2>>>
    = i2 < i1 ? 1 : 2;


  template<int_ i1, int_ i2>
  constexpr int smp_if_reduce_tc_v<size<greater_equal_than_c<i1>>, size<greater_equal_than_c<i2>>>
    = i1 >= i2 ? 1 : 2;

  template<int_ i1, int_ i2>
  constexpr int smp_if_reduce_tc_v<size<greater_equal_than_c<i1>>, size<greater_than_c<i2>>>
    = i1 > i2 ? 1 : 2;

  template<int_ i1, int_ i2>
  constexpr int smp_if_reduce_tc_v<size<greater_than_c<i1>>, size<greater_than_c<i2>>>
    = i1 >= i2 ? 1 : 2;

  template<int_ i1, int_ i2>
  constexpr int smp_if_reduce_tc_v<size<greater_than_c<i1>>, size<greater_equal_than_c<i2>>>
    = i2 > i1 ? 1 : 2;


  template<int n> struct smp_if_select_tc;
  template<> struct smp_if_select_tc<0>
  {
    template<class Pred, class TC, class FC>
    using f = if_<Pred, TC, FC>;
  };
  template<> struct smp_if_select_tc<1> : smp_if_select_tc<0> {};
  template<> struct smp_if_select_tc<2> { template<class, class TC, class> using f = TC; };
  template<> struct smp_if_select_tc<3> { template<class, class, class FC> using f = FC; };

  template<int> struct smp_if_select_fc;
  template<> struct smp_if_select_fc<0> : smp_if_select_tc<0> {};
  template<> struct smp_if_select_fc<1> : smp_if_select_tc<3> {};
  template<> struct smp_if_select_fc<2> : smp_if_select_tc<3> {};
  template<> struct smp_if_select_fc<3> : smp_if_select_tc<2> {};

  template<class> constexpr bool smp_if_safe_pred_v = false;
  template<> inline constexpr bool smp_if_safe_pred_v<size<>> = true;
  template<class x> constexpr bool smp_if_safe_pred_v<size<is<x>>> = true;
  template<class x> constexpr bool smp_if_safe_pred_v<size<is<x, not_<>>>> = true;
  template<int_ i> constexpr bool smp_if_safe_pred_v<size<less_than_c<i>>> = true;
  template<int_ i> constexpr bool smp_if_safe_pred_v<size<less_equal_than_c<i>>> = true;
  template<int_ i> constexpr bool smp_if_safe_pred_v<size<greater_than_c<i>>> = true;
  template<int_ i> constexpr bool smp_if_safe_pred_v<size<greater_equal_than_c<i>>> = true;
  template<int_ i> constexpr bool smp_if_safe_pred_v<size<equal_to_c<i>>> = true;
  template<class F> constexpr bool smp_if_safe_pred_v<contract<F>> = smp_if_safe_pred_v<F>;

  template<bool>
  struct smp_if_base;

  template<>
  struct smp_if_base<true>
  {
    template<int_, class Pred, class TC, class FC>
    using f = test_contract<Pred, TC, FC>;
  };

  template<>
  struct smp_if_base<false>
  {
    template<int_, class Pred, class TC, class FC>
    using f = contract<
      invoke_twice<
        typename optimize_try<
          try_<
            Pred,
            try_<
              to_bool<>,
              if_<identity, always<TC>, always<FC>>,
              always<violation>
            >,
            always<violation>
          >
        >::type
      >
    >;
  };

  template<class Pred, class TC, class FC>
  struct smp_if_impl<if_<Pred, TC, FC>, false>
  {
    using type = typename smp_if_base<smp_if_safe_pred_v<Pred>>
      ::template f<0, Pred, TC, FC>;
  };

  template<class F>
  struct smp_if_impl<F, true> : smp_if_impl<F, false>
  {};

  template<class Pred, class TC, class FC, bool = true>
  struct smp_if_simplify_pred
  {
    using type = if_<Pred, TC, FC>;
  };

  // if_<pred, if_, if_>

  template<class Pred, class Pred1, class TC1, class FC1, class Pred2, class TC2, class FC2>
  struct smp_if_simplify_pred<Pred, if_<Pred1, TC1, FC1>, if_<Pred2, TC2, FC2>, true>
  : smp_if_simplify_pred<
      Pred,
      typename smp_if_select_tc<smp_if_reduce_tc_v<Pred, Pred1>>::template f<Pred1, TC1, FC1>,
      typename smp_if_select_fc<smp_if_reduce_tc_v<Pred, Pred2>>::template f<Pred2, TC2, FC2>,
      (smp_if_reduce_tc_v<Pred, Pred1> > 0) || smp_if_reduce_tc_v<Pred, Pred2> != 0
    >
  {};

  template<class Pred, class Pred1, class TC1, class FC1, class Pred2, class TC2, class FC2>
  struct smp_if_impl<if_<Pred, if_<Pred1, TC1, FC1>, if_<Pred2, TC2, FC2>>, true>
    : smp_if_impl<
      typename smp_if_simplify_pred<Pred, if_<Pred1, TC1, FC1>, if_<Pred2, TC2, FC2>>::type,
      false
    >
  {};

  // if_<pred, if_, F>

  template<class Pred, class Pred1, class TC1, class FC1, class FC2>
  struct smp_if_simplify_pred<Pred, if_<Pred1, TC1, FC1>, FC2, true>
  : smp_if_simplify_pred<
      Pred,
      typename smp_if_select_tc<smp_if_reduce_tc_v<Pred, Pred1>>::template f<Pred1, TC1, FC1>,
      FC2,
      (smp_if_reduce_tc_v<Pred, Pred1> > 0)
    >
  {};

  template<class Pred, class Pred1, class TC1, class FC1, class FC2>
  struct smp_if_impl<if_<Pred, if_<Pred1, TC1, FC1>, FC2>, true>
    : smp_if_impl<
      typename smp_if_simplify_pred<Pred, if_<Pred1, TC1, FC1>, FC2>::type,
      false
    >
  {};

  // if_<pred, F, if_>

  template<class Pred, class TC1, class Pred2, class TC2, class FC2>
  struct smp_if_simplify_pred<Pred, TC1, if_<Pred2, TC2, FC2>, true>
  : smp_if_simplify_pred<
      Pred,
      TC1,
      typename smp_if_select_fc<smp_if_reduce_tc_v<Pred, Pred2>>::template f<Pred2, TC2, FC2>,
      smp_if_reduce_tc_v<Pred, Pred2> != 0
    >
  {};

  template<class Pred, class TC1, class Pred2, class TC2, class FC2>
  struct smp_if_impl<if_<Pred, TC1, if_<Pred2, TC2, FC2>>, true>
    : smp_if_impl<
      typename smp_if_simplify_pred<Pred, TC1, if_<Pred2, TC2, FC2>>::type,
      false
    >
  {};


  // if_<pred, always, always>

  template<bool> struct smp_if_always;

  template<>
  struct smp_if_always<false>
  {
    template<class Pred, class TC, class FC>
    using f = try_contract<
      Pred,
      try_<
        to_bool<>,
        if_<identity, TC, FC>
      >
    >;
  };

  template<>
  struct smp_if_always<true>
  {
    template<class Pred, class TC, class FC>
    using f = test_contract<Pred, TC, FC>;
  };

  template<class Pred, class True, class False>
  struct smp_if_impl<if_<Pred, always<True>, always<False>>, false>
  {
    using type = typename smp_if_always<smp_if_safe_pred_v<Pred>>
      ::template f<Pred, always<True>, always<False>>;
  };


  // if_<pred, front|drop_front, front|drop_front>

  template<bool> struct smp_if_select;

  template<>
  struct smp_if_select<false> : smp_if_base<false>
  {};

  template<>
  struct smp_if_select<true>
  {
    template<int_ min_index, class Pred, class TC, class FC>
    using f = contract<typename smp_if_simplify_pred<
      size<greater_than_c<min_index>>,
      if_<Pred, TC, FC>,
      violation
    >::type>;
  };

  template<bool>
  struct smp_select_pred_unary_or_binary
  {
    template<class Pred>
    using f = assume_unary_or_more<Pred>;
  };

  template<>
  struct smp_select_pred_unary_or_binary<false>
  {
    template<class Pred>
    using f = assume_binary_or_more<Pred>;
  };


  // if_<pred, front, front>

  template<class Pred, class TC, class FC>
  struct smp_if_impl<if_<Pred, try_<front<TC>>, try_<front<FC>>>, false>
  {
    using type = typename smp_if_select<smp_if_safe_pred_v<Pred>>
      ::template f<0, assume_unary_or_more<Pred>, front<TC>, front<FC>>;
  };

  // if_<pred, front, drop_front>

  template<class Pred, class TC, class FC, int_ min_index, unsigned ndrop>
  struct smp_if_impl<
    if_<
      Pred,
      try_<front<TC>>,
      if_<size<greater_than_c<min_index>>, drop_front_c<ndrop, front<FC>>, violation>
    >,
    false
  >
  {
    using type = typename conditional_c<min_index < ndrop>::template f<
      bad_contract,
      typename smp_if_select<smp_if_safe_pred_v<Pred>>::template f<
        min_index,
        typename smp_select_pred_unary_or_binary<min_index == 0>::template f<Pred>,
        front<TC>,
        drop_front_c<ndrop, front<FC>>
      >
    >;
  };

  // if_<pred, drop_front, front>

  template<class Pred, class TC, class FC, int_ min_index, unsigned ndrop>
  struct smp_if_impl<
    if_<
      Pred,
      if_<size<greater_than_c<min_index>>, drop_front_c<ndrop, front<TC>>, violation>,
      try_<front<FC>>
    >,
    false
  >
  {
    using type = typename conditional_c<min_index < ndrop>::template f<
      bad_contract,
      typename smp_if_select<smp_if_safe_pred_v<Pred>>::template f<
        min_index,
        typename smp_select_pred_unary_or_binary<min_index == 0>::template f<Pred>,
        drop_front_c<ndrop, front<TC>>,
        front<FC>
      >
    >;
  };

  // if_<pred, drop_front, drop_front>

  template<class Pred, class TC, class FC, int_ min_indexT, int_ min_indexF, unsigned ndropT, unsigned ndropF>
  struct smp_if_impl<
    if_<
      Pred,
      if_<size<greater_than_c<min_indexT>>, drop_front_c<ndropT, front<TC>>, violation>,
      if_<size<greater_than_c<min_indexF>>, drop_front_c<ndropF, front<FC>>, violation>
    >,
    false
  >
  {
    static constexpr int_ max_index = min_indexT < min_indexF ? min_indexF : min_indexT;

    using type = typename conditional_c<max_index < ndropT || max_index < ndropF>::template f<
      bad_contract,
      typename smp_if_select<smp_if_safe_pred_v<Pred>>::template f<
        max_index,
        typename smp_select_pred_unary_or_binary<max_index == 0>::template f<Pred>,
        drop_front_c<ndropT, try_<TC>>,
        drop_front_c<ndropF, front<FC>>
      >
    >;
  };
}
/// \endcond
