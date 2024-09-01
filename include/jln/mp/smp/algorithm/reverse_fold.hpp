// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/rotate.hpp>
#include <jln/mp/smp/functional/if.hpp>
#include <jln/mp/smp/list/size.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/algorithm/reverse_fold.hpp>
#include <jln/mp/functional/monadic.hpp>

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using reverse_fold = test_contract<
    mp::size<>,
    mp::reverse_fold<
      mp::monadic0<assume_binary<F>>,
      mp::monadic<assume_unary<C>>>>;

  template<class F, class EmptyC, class C = identity>
  using reverse_fold_or_else = contract<
    mp::reverse_fold_or_else<
      mp::monadic0<assume_binary<F>>,
      subcontract<EmptyC>,
      mp::monadic<assume_unary<C>>>>;

  template<class F, class FallbackValue, class C = identity>
  using reverse_fold_or = reverse_fold_or_else<F,
    contract<mp::always<FallbackValue>>, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, reverse_fold<F, C>>
  {
    using type = smp::reverse_fold<sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class EmptyC, class C>
  struct _sfinae<sfinae, if_<size<>, rotate_c<-1, reverse_fold<F, C>>, EmptyC>>
  {
    using type = smp::reverse_fold_or_else<sfinae<F>, sfinae<EmptyC>, sfinae<C>>;
  };
}
/// \endcond
