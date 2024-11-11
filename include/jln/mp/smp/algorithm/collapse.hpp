// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/collapse.hpp>
#include <jln/mp/detail/smp_listify_or_monadic_xs.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class L>
  struct make_smp_collapse;
}
/// \endcond

namespace jln::mp::smp
{
  template<class C, class F, class... keys>
  using collapse2_with = try_contract<mp::collapse2_with<
    typename detail::smp_listify_or_monadic_xs<F>::template f<C>,
    subcontract<F>,
    keys...
  >>;

  template<class C, class F, int_t... keys>
  using collapse2_with_c = try_contract<mp::collapse2_with<
    typename detail::smp_listify_or_monadic_xs<F>::template f<C>,
    subcontract<F>,
    number<keys>...
  >>;

  template<class C, class... keys>
  using collapse2 = try_contract<mp::collapse2_with<assume_lists<C>, mp::listify, keys...>>;

  template<class C, int_t... keys>
  using collapse2_c = try_contract<
    mp::collapse2_with<assume_lists<C>, mp::listify, number<keys>...>>;


  template<class keys, class F = listify, class C = listify>
  using collapse_with = typename detail::make_smp_collapse<keys>
    ::template f<F, C>;

  template<class keys, class C = listify>
  using collapse = typename detail::make_smp_collapse<keys>
    ::template f<listify, C>;


  template<class... keys>
  using collapse_for = try_contract<mp::collapse2_with<mp::listify, mp::listify, keys...>>;

  template<bool... keys>
  using collapse_for_c = try_contract<mp::collapse2_with<mp::listify, mp::listify, number<keys>...>>;
}

/// \cond
namespace jln::mp::detail
{
  template<class L>
  struct make_smp_collapse : always<bad_contract>
  {};

  template<template<class...> class Tpl, class... keys>
  struct make_smp_collapse<Tpl<keys...>>
  {
    template<class C, class F>
    using f = smp::collapse2_with<C, F, keys...>;
  };


  template<template<class> class sfinae, class C, class F, class... keys>
  struct _sfinae<sfinae, collapse2_with<C, F, keys...>>
  {
    using type = smp::collapse2_with<sfinae<C>, sfinae<F>, keys...>;
  };
}
/// \endcond
