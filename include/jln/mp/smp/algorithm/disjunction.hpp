// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/conjunction.hpp>
#include <jln/mp/algorithm/disjunction.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using disjunction_with = detail::conjunction_disjunction_with<
    mp::drop_until, true_, false_, Pred, C>;

  template<class C = identity>
  using disjunction = disjunction_with<identity, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, disjunction_with<Pred, C>>
  {
    using type = smp::disjunction_with<sfinae<Pred>, sfinae<C>>;
  };
}
/// \endcond
