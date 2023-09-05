// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/algorithm/reverse_fold.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/list/size.hpp>

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using reverse_fold = test_contract<
    mp::size<>,
    mp::reverse_fold<
      mp::monadic0<assume_unary<F>>,
      mp::monadic<subcontract<C>>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, reverse_fold<F, C>>
  {
    using type = smp::reverse_fold<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
