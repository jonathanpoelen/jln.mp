// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/utility/value_type.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using value_type = try_contract<mp::value_type<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, value_type<C>>
  {
    using type = smp::value_type<sfinae<C>>;
  };
}
/// \endcond
