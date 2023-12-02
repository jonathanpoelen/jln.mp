// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/compose.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/functional/lift.hpp>
#include <jln/mp/smp/functional/tee.hpp>

namespace jln::mp::smp
{
  template<template<class...> class F, template<class...> class... Fs>
  using compose_f = mp::detail::sfinae<
    mp::compose<mp::lift<F>, mp::lift<Fs>...>
  >;

  template<class F, class... Fs>
  using compose = mp::detail::sfinae<
    mp::compose<subcontract_barrier<F>, subcontract_barrier<Fs>...>
  >;
}
