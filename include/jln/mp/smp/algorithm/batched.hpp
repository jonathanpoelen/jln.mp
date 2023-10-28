// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/batched.hpp>

namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using batched_c = contract<mp::batched_c<n, assume_lists<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(batched, (N), (C, smp::listify), smp::batched_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, int_ n, class C>
  struct _sfinae<sfinae, batched_c<n, C>>
  {
    using type = smp::batched_c<n, sfinae<C>>;
  };
}
/// \endcond
