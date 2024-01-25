// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/smp/algorithm/is_sorted.hpp>
#include <jln/mp/algorithm/sort.hpp>

namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = listify>
  using sort = contract<mp::sort<
    concepts::predicate_or_else<assume_binary<Cmp>, mp::always<true_>>,
    mp::if_<
      mp::try_or<is_sorted<Cmp>, false_>,
      subcontract<C>,
      violation
    >
  >>;

  template<class Cmp = less<>, class C = listify>
  using stable_sort = sort<Cmp, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, sort<Cmp, C>>
  {
    using type = smp::sort<sfinae<Cmp>, sfinae<C>>;
  };
}
/// \endcond
