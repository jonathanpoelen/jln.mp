// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/as_number.hpp>
#include <jln/mp/smp/functional/identity.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using as_number = try_contract<mp::as_number<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, as_number<C>>
  {
    using type = smp::as_number<sfinae<C>>;
  };
}
/// \endcond
