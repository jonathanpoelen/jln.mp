// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/rotate.hpp>
#include <type_traits> // std::void_t

namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using rotate_c = contract<mp::rotate_c<n, subcontract<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(rotate, (N), (C, smp::listify), smp::rotate_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, int_ N, class C>
  struct _sfinae<sfinae, rotate_c<N, C>>
  {
    using type = smp::rotate_c<N, sfinae<C>>;
  };
}
/// \endcond
