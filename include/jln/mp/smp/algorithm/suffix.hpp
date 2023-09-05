// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/suffix.hpp>
#include <jln/mp/smp/list/listify.hpp>

namespace jln::mp::smp
{
  template<class x, class C = listify>
  using suffix = contract<mp::suffix<x, subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, suffix<x, C>>
  {
    using type = smp::suffix<x, sfinae<C>>;
  };
}
/// \endcond
