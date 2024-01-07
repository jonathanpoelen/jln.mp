// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/pairwise.hpp>
#include <jln/mp/detail/smp_listify_or_monadic_xs.hpp>

namespace jln::mp::smp
{
  template<class F = listify, class C = listify>
  using pairwise_with = contract<mp::pairwise_with<
    assume_binary<F>,
    typename detail::smp_listify_or_monadic_xs<F>::template f<C>
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
