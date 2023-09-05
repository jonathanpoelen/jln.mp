// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/split.hpp>
#include <jln/mp/algorithm/split_after.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using split_after_if = try_contract<
    mp::split_after_if<assume_unary<Pred>, assume_lists<C>>>;

  template<class x, class C = listify>
  using split_after = contract<mp::split_after<x, assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, split_after_if<F, C>>
  {
    using type = smp::split_after_if<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
