// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/utility/is.hpp>

namespace jln::mp::smp
{
  template<class x, class C = identity>
  using is = try_contract<mp::is<x, assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, is<x, C>>
  {
    using type = smp::is<x, sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT2(argument_category::unary, is);
}
/// \endcond
