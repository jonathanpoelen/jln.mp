// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/bind_back.hpp>

namespace jln::mp::smp
{
  template<class F, class... BoundArgs>
  using bind_back = contract<mp::bind_back<subcontract<F>, BoundArgs...>>;

  template<class F, int_... BoundArgs>
  using bind_back_c = bind_back<F, number<BoundArgs>...>;

#if JLN_MP_ENABLE_TPL_AUTO
  template<class F, auto... BoundArgs>
  using bind_back_v = bind_back<F, val<BoundArgs>...>;
#endif
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
