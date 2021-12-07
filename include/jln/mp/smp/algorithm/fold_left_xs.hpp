#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/algorithm/fold_left_xs.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/list/size.hpp>

namespace jln::mp::smp
{
  template<int_ OffsetEnd, class F, class C = identity>
  using partial_fold_left_xs_c = test_contract<
    mp::size<>,
    mp::partial_fold_left_xs_c<
      OffsetEnd,
      mp::monadic_xs<subcontract<F>>,
      mp::monadic<assume_unary<C>>>>;

  template<class F, class C = identity>
  using fold_left_xs = test_contract<
    mp::size<>,
    mp::fold_left_xs<
      mp::monadic_xs<subcontract<F>>,
      mp::monadic<assume_unary<C>>>>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(partial_fold_left_xs, (OffsetEnd), (F), (C, smp::identity),
  smp::partial_fold_left_xs_c<OffsetEnd::value, F, C>)


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, int_ OffsetEnd, class F, class C>
  struct _sfinae<sfinae, partial_fold_left_xs_c<OffsetEnd, F, C>>
  {
    using type = smp::partial_fold_left_xs_c<OffsetEnd, sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, fold_left_xs<F, C>>
  {
    using type = smp::fold_left_xs<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
