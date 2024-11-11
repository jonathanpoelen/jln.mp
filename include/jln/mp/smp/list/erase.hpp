// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/erase.hpp>
#include <type_traits> // std::void_t

namespace jln::mp::smp
{
  template<int_ start, unsigned size = 1, class C = listify>
  using erase_c = contract<mp::erase_c<start, size, subcontract<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(erase, (start), (size, number<1>), (C, smp::listify),
  smp::erase_c<start::value, size::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, int_ start, unsigned size, class C>
  struct _sfinae<sfinae, erase_c<start, size, C>>
  {
    using type = smp::erase_c<start, size, sfinae<C>>;
  };
}
/// \endcond
