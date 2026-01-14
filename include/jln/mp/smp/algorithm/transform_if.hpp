// SPDX-FileCopyrightText: 2026 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/at.hpp>
#include <jln/mp/smp/functional/if.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/algorithm/transform_if.hpp>

namespace jln::mp::smp
{
  template<class Pred, class F, class C = listify>
  using transform_if = contract<
    mp::transform<
      if_<
        assume_unary_barrier<Pred>,
        assume_unary_barrier<F>,
        contract<mp::at0<>>
      >,
      mp::monadic_xs<subcontract<C>>
    >
  >;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class F, class C>
  struct _sfinae<sfinae, transform_if<Pred, F, C>>
  {
    using type = smp::transform_if<sfinae<Pred>, sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
