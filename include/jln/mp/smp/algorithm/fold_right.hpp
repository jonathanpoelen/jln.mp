// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/algorithm/fold_right.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/list/size.hpp>

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using fold_right = test_contract<
    mp::size<>,
    mp::fold_right<
      mp::monadic0<assume_binary<F>>,
      mp::monadic<subcontract<C>>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, fold_right<F, C>>
  {
    using type = smp::fold_right<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
