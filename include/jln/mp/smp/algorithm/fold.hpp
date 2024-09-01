// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/if.hpp>
#include <jln/mp/smp/list/size.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/algorithm/fold.hpp>
#include <jln/mp/functional/monadic.hpp>

namespace jln::mp::smp
{
  template<class F, class EmptyC, class C = identity>
  using fold_or_else = test_contract<
    mp::size<>,
    mp::fold<
      mp::monadic0<assume_binary<F>>,
      mp::monadic<assume_unary<C>>
    >,
    subcontract<EmptyC>
  >;

  template<class F, class FallbackValue, class C = identity>
  using fold_or = fold_or_else<F, contract<mp::always<FallbackValue>>, C>;

  template<class F, class C = identity>
  using fold = fold_or_else<F, bad_contract, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, fold<F, C>>
  {
    using type = smp::fold<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
