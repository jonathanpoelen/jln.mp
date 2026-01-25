// SPDX-FileCopyrightText: 2026 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/functional/sfinaefwd.hpp>
#include <jln/mp/utility/conditional.hpp>

namespace jln::mp::smp
{
  template<bool b>
  using conditional_c = try_contract<mp::conditional_c<b>>;
}

JLN_MP_MAKE_REGULAR_SMP1_P(conditional, (x), smp::conditional_c<JLN_MP_RAW_EXPR_TO_BOOL(x::value)>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, bool b>
  struct _sfinae<sfinae, conditional_c<b>>
  {
    using type = smp::conditional_c<b>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT(argument_category::binary, (bool b), (conditional_c<b>));
}
/// \endcond
