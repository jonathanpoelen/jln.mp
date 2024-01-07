// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/circulant_matrix.hpp>
#include <jln/mp/detail/smp_listify_or_monadic_xs.hpp>

namespace jln::mp::smp
{
  template<class F = listify, class C = listify>
  using circulant_matrix_with = contract<mp::circulant_matrix_with<
    assume_unary_or_more<F>,
    typename detail::smp_listify_or_monadic_xs<F>::template f<C>
  >>;

  template<class C = listify>
  using circulant_matrix = contract<mp::circulant_matrix_with<mp::listify, assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, circulant_matrix_with<F, C>>
  {
    using type = smp::circulant_matrix_with<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
