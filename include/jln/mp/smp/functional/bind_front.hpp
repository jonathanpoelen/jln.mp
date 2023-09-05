// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/bind_front.hpp>

namespace jln::mp::smp
{
  template<class F, class... BoundArgs>
  using bind_front = contract<mp::bind_front<subcontract<F>, BoundArgs...>>;

  template<class F, int_... BoundArgs>
  using bind_front_c = bind_front<F, number<BoundArgs>...>;

#if JLN_MP_ENABLE_TPL_AUTO
  template<class F, auto... BoundArgs>
  using bind_front_v = bind_front<F, val<BoundArgs>...>;
#endif
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
