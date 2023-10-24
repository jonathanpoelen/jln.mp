// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/split.hpp>
#include <jln/mp/algorithm/split_keep_separator.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using split_keep_separator_if = try_contract<
    mp::split_keep_separator_if<assume_unary<Pred>, assume_lists<C>>>;

  template<class x, class C = listify>
  using split_keep_separator = contract<mp::split_keep_separator<x, assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, split_keep_separator_if<F, C>>
  {
    using type = smp::split_keep_separator_if<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
