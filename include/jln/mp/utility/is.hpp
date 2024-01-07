// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/algorithm/same_xs.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/functional/identity.hpp>

namespace jln::mp
{
  /// \ingroup utility

  /// \treturn \bool
  template<class T, class C = identity>
  struct is
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_IS_SAME(T, x)>);
  };

  /// \cond
  template<class T>
  struct is<T, identity>
  {
    template<class x>
    using f = number<JLN_MP_IS_SAME(T, x)>;
  };
  /// \endcond
} // namespace jln::mp
