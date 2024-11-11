// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/if.hpp>
#include <jln/mp/smp/list/size.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/algorithm/fold_xs.hpp>
#include <jln/mp/functional/monadic.hpp>

namespace jln::mp::smp
{
  template<int_ OffsetEnd, class F, class EmptyC, class C = identity>
  using partial_fold_xs_or_else_c = test_contract<
    mp::size<>,
    mp::partial_fold_xs_c<
      OffsetEnd,
      mp::monadic_xs<assume_binary_or_more<F>>,
      mp::monadic<assume_unary<C>>
    >,
    subcontract<EmptyC>
  >;

  template<int_ OffsetEnd, class F, class C = identity>
  using partial_fold_xs_c = partial_fold_xs_or_else_c<OffsetEnd, F, bad_contract, C>;

  template<class F, class C = identity>
  using fold_xs = partial_fold_xs_or_else_c<-1, F, bad_contract, C>;

  template<int_ OffsetEnd, class F, class FallbackValue, class C = identity>
  using partial_fold_xs_or_c = partial_fold_xs_or_else_c<
    OffsetEnd, F, contract<mp::always<FallbackValue>>, C>;

  template<class F, class FallbackValue, class C = identity>
  using fold_xs_or = partial_fold_xs_or_else_c<
    -1, F, contract<mp::always<FallbackValue>>, C>;

  template<class F, class EmptyC = F, class C = identity>
  using fold_xs_or_else = partial_fold_xs_or_else_c<-1, F, EmptyC, C>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(partial_fold_xs, (OffsetEnd), (F), (C, smp::identity),
  smp::partial_fold_xs_or_else_c<OffsetEnd::value, F, bad_contract, C>)

JLN_MP_MAKE_REGULAR_SMP4_P(partial_fold_xs_or, (OffsetEnd), (F), (FallbackValue), (C, smp::identity),
  smp::partial_fold_xs_or_else_c<OffsetEnd::value, F, contract<always<FallbackValue>>, C>)

JLN_MP_MAKE_REGULAR_SMP4_P(partial_fold_xs_or_else, (OffsetEnd), (F), (EmptyC), (C, smp::identity),
  smp::partial_fold_xs_or_else_c<OffsetEnd::value, F, EmptyC, C>)


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, int_ OffsetEnd, class F, class C>
  struct _sfinae<sfinae, partial_fold_xs_c<OffsetEnd, F, C>>
  {
    using type = smp::partial_fold_xs_c<OffsetEnd, sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
