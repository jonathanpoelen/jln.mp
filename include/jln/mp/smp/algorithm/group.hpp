// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/smp_listify_or_monadic_xs.hpp>
#include <jln/mp/smp/algorithm/same.hpp>
#include <jln/mp/algorithm/group.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Cmp>
  struct smp_group_contract;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Cmp, class F = listify, class C = listify>
  using group_by_with = typename detail::smp_group_contract<assume_binary<Cmp>>
    ::template f<
      subcontract<F>,
      typename detail::smp_listify_or_monadic_xs<subcontract<F>>::template f<C>
    >;

  template<class Cmp, class C = listify>
  using group_by = typename detail::smp_group_contract<assume_binary<Cmp>>
    ::template f<mp::listify, assume_lists<C>>;

  template<class F = listify, class C = listify>
  using group_with = contract<mp::group_by_with<
    mp::same<>,
    subcontract<F>,
    typename detail::smp_listify_or_monadic_xs<subcontract<F>>::template f<C>
  >>;

  template<class C = listify>
  using group = contract<mp::group_by_with<mp::same<>, mp::listify, assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<class Cmp>
  struct smp_group_contract
  {
    template<class F, class C>
    using f = try_contract<group_by_with<typename optimize_try<try_<Cmp>>::type, F, C>>;
  };

  template<>
  struct smp_group_contract<same<>>
  {
    template<class F, class C>
    using f = contract<group_by_with<same<>, F, C>>;
  };


  template<template<class> class sfinae, class Cmp, class F, class C>
  struct _sfinae<sfinae, group_by_with<Cmp, F, C>>
  {
    using type = smp::group_by_with<sfinae<Cmp>, sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
