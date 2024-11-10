// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/detail/first.hpp>

namespace jln::mp
{
  /// \ingroup utility

  /// Always evaluate at an arbitrary value.
  /// \post result = x
  /// \treturn \value
  template<class x, class C = identity>
  struct always
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_LAZY_PARAM_T(xs, x));
  };

  /// \cond
  template<class x>
  struct always<x, identity>
  {
    template<class... xs>
    using f = JLN_MP_LAZY_PARAM_T(xs, x);
  };
  /// \endcond
}
