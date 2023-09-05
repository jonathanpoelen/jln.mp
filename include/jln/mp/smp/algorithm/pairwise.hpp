// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/algorithm/circulant_matrix.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/algorithm/pairwise.hpp>

namespace jln::mp::smp
{
  template<class F = listify, class C = listify>
  using pairwise_with = contract<mp::pairwise_with<
    assume_binary<F>, detail::smp_listify_or_monadic_xs<F, C>
  >>;

  template<class C = listify>
  using pairwise = contract<mp::pairwise<assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, pairwise_with<F, C>>
  {
    using type = smp::pairwise_with<sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, pairwise<C>>
  {
    using type = smp::pairwise<sfinae<C>>;
  };
}
/// \endcond
