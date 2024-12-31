// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/utility/is_base_of.hpp>

namespace jln::mp::smp
{
  template<class Derived, class C = identity>
  using is_base_of = try_contract<mp::is_base_of<Derived, assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Derived, class C>
  struct _sfinae<sfinae, is_base_of<Derived, C>>
  {
    using type = smp::is_base_of<Derived, sfinae<C>>;
  };
}
/// \endcond
