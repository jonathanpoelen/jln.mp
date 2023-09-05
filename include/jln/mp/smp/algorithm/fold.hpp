// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/algorithm/fold.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/list/size.hpp>

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using fold = test_contract<
    mp::size<>,
    mp::fold<
      mp::monadic0<assume_binary<F>>,
      mp::monadic<assume_unary<C>>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, fold<F, C>>
  {
    using type = smp::fold<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
