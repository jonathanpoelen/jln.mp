// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/clear.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using clear = contract<mp::clear<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, clear<C>>
  {
    using type = smp::clear<sfinae<C>>;
  };
}
/// \endcond
