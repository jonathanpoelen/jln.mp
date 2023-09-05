// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/scan.hpp>
#include <jln/mp/functional/monadic.hpp>

namespace jln::mp::smp
{
  template<class F, class C = listify>
  using scan = contract<mp::scan<
    monadic_xs<assume_binary<F>>,
    monadic_xs<subcontract<C>>
  >>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, scan<F, C>>
  {
    using type = smp::scan<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
