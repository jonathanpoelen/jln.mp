// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/number/is_number.hpp>
#include <jln/mp/smp/functional/identity.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using is_number = try_contract<mp::is_number<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, is_number<C>>
  {
    using type = smp::is_number<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::unary, is_number);
}
/// \endcond
