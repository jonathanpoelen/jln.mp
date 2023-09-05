// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/memoize.hpp>

namespace jln::mp::smp
{
  template <class C>
  using memoize = contract<memoize<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, memoize<C>>
  {
    using type = smp::memoize<sfinae<C>>;
  };
}
/// \endcond
