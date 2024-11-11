// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/bind_back.hpp>

namespace jln::mp::smp
{
  template<class F, class... BoundArgs>
  using bind_back = contract<mp::bind_back<subcontract<F>, BoundArgs...>>;

  template<class F, int_t... BoundArgs>
  using bind_back_c = bind_back<F, number<BoundArgs>...>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class... BoundArgs>
  struct _sfinae<sfinae, bind_back<F, BoundArgs...>>
  {
    using type = smp::bind_back<sfinae<F>, BoundArgs...>;
  };
}
/// \endcond
