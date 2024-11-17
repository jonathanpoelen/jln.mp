// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/bind_front.hpp>

namespace jln::mp::smp
{
  template<class F, class... BoundArgs>
  using bind_front = contract<mp::bind_front<subcontract<F>, BoundArgs...>>;

  template<class F, int_t... BoundArgs>
  using bind_front_c = bind_front<F, number<BoundArgs>...>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class... BoundArgs>
  struct _sfinae<sfinae, bind_front<F, BoundArgs...>>
  {
    using type = smp::bind_front<sfinae<F>, BoundArgs...>;
  };
}
/// \endcond
