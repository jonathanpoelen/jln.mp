// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/contract.hpp>
#include <jln/mp/algorithm/repeat_index.hpp>
#include <jln/mp/detail/smp_listify_or_monadic_xs.hpp>

namespace jln::mp::smp
{
  template<class F = listify, class C = listify>
  using repeat_index_with = try_contract<
    mp::repeat_index_with<
      subcontract<F>,
      typename detail::smp_listify_or_monadic_xs<F>::template f<C>
    >
  >;

  template<class C = listify>
  using repeat_index = try_contract<
    mp::repeat_index_with<mp::listify, subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, repeat_index_with<F, C>>
  {
    using type = smp::repeat_index_with<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
