// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/number/number.hpp>

namespace jln::mp
{
  /// \ingroup number

  /// Narrowing convertion from \value to \bool.
  /// \treturn \bool
  template<class C = identity>
  struct as_bool
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<bool{x::value}>);
  };

  namespace emp
  {
    template<class x>
    using as_bool = number<bool{x::value}>;
  }

  /// \cond
  template<>
  struct as_bool<identity>
  {
    template<class x>
    using f = number<bool{x::value}>;
  };
  /// \endcond
}
