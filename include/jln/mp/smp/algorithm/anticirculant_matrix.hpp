// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/smp_listify_or_monadic_xs.hpp>
#include <jln/mp/algorithm/anticirculant_matrix.hpp>

namespace jln::mp::smp
{
  template<class F = listify, class C = listify>
  using anticirculant_matrix_with = contract<mp::anticirculant_matrix_with<
    assume_unary_or_more<F>,
    typename detail::smp_listify_or_monadic_xs<F>::template f<C>
  >>;

  template<class C = listify>
  using anticirculant_matrix = contract<mp::anticirculant_matrix<assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, anticirculant_matrix_with<F, C>>
  {
    using type = smp::anticirculant_matrix_with<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
