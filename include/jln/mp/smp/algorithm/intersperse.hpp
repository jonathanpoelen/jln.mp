// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/intersperse.hpp>
#include <jln/mp/smp/list/listify.hpp>

namespace jln::mp::smp
{
  template<class x, class C = listify>
  using intersperse = contract<mp::intersperse<x, subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, intersperse<x, C>>
  {
    using type = smp::intersperse<x, sfinae<C>>;
  };
}
/// \endcond
