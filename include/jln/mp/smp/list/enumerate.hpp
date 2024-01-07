// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/smp_listify_or_monadic_xs.hpp>
#include <jln/mp/list/enumerate.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using enumerate = contract<mp::enumerate_with<mp::listify, subcontract<C>>>;

  template<class F = listify, class C = listify>
  using enumerate_with = contract<enumerate_with<
    assume_binary<F>,
    typename detail::smp_listify_or_monadic_xs<F>::template f<C>
  >>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, enumerate_with<F, C>>
  {
    using type = smp::enumerate_with<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
