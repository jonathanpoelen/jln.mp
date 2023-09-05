// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/reverse.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using reverse = contract<mp::reverse<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, reverse<C>>
  {
    using type = smp::reverse<sfinae<C>>;
  };
}
/// \endcond
