// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/if.hpp>
#include <jln/mp/smp/list/size.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/algorithm/fold_tree.hpp>
#include <jln/mp/functional/monadic.hpp>

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using fold_tree = contract<mp::fold_tree<
    mp::monadic_xs<assume_binary<F>>,
    mp::monadic_xs<subcontract<C>>>>;

  template<class F, class EmptyC, class C = identity>
  using fold_tree_or_else = contract<
    mp::fold_tree_or_else<
      mp::monadic_xs<assume_binary<F>>,
      subcontract<EmptyC>,
      mp::monadic_xs<subcontract<C>>>>;

  template<class F, class FallbackValue, class C = identity>
  using fold_tree_or = fold_tree_or_else<F, contract<mp::always<FallbackValue>>, C>;

  template<class F, class C = identity>
  using fold_balanced_tree = contract<mp::fold_balanced_tree<
    mp::monadic_xs<assume_binary<F>>,
    mp::monadic_xs<subcontract<C>>>>;

  template<class F, class EmptyC, class C = identity>
  using fold_balanced_tree_or_else = contract<
    mp::fold_balanced_tree_or_else<
      mp::monadic_xs<assume_binary<F>>,
      subcontract<EmptyC>,
      mp::monadic_xs<subcontract<C>>>>;

  template<class F, class FallbackValue, class C = identity>
  using fold_balanced_tree_or = fold_balanced_tree_or_else<F, contract<mp::always<FallbackValue>>, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, fold_tree<F, C>>
  {
    using type = smp::fold_tree<sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, fold_balanced_tree<F, C>>
  {
    using type = smp::fold_balanced_tree<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
