// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/number/number.hpp>

namespace jln::mp
{
  /// \ingroup number

  /// Converts a \value to a \bool.
  /// \treturn \bool
  template<class C = identity>
  struct to_bool
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_RAW_EXPR_TO_BOOL(x::value)>);
  };

  namespace emp
  {
    template<class x>
    using to_bool = number<JLN_MP_RAW_EXPR_TO_BOOL(x::value)>;
  }

  /// \cond
  template<>
  struct to_bool<identity>
  {
    template<class x>
    using f = number<JLN_MP_RAW_EXPR_TO_BOOL(x::value)>;
  };
  /// \endcond
}
