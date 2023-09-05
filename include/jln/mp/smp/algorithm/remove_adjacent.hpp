// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/pairwise_fold.hpp>
#include <jln/mp/algorithm/remove_adjacent.hpp>

namespace jln::mp::smp
{
  template<class BinaryPred, class C = listify>
  using remove_adjacent_if = contract<mp::pairwise_fold_and_transform_front<
    if_<assume_binary<BinaryPred>, contract<mp::always<mp::list<>>>, contract<mp::pop_front<>>>,
    mp::listify,
    mp::monadic_xs<mp::join<subcontract<C>>>
  >>;

  template<class C = listify>
  using remove_adjacent = remove_adjacent_if<contract<mp::same<>>, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class BinaryPred, class C>
  struct _sfinae<sfinae, remove_adjacent_if<BinaryPred, C>>
  {
    using type = smp::remove_adjacent_if<sfinae<BinaryPred>, sfinae<C>>;
  };
}
/// \endcond
