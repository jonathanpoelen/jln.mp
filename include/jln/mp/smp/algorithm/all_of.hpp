// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/drop_while.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/algorithm/all_of.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using all_of = drop_while<Pred,
    always<false_, assume_positive_number_barrier<C>>,
    always<true_, assume_positive_number_barrier<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, all_of<Pred, C>>
  {
    using type = smp::all_of<sfinae<Pred>, sfinae<C>>;
  };
}
/// \endcond
