// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/functional/identity.hpp>

#include <type_traits>

namespace jln::mp
{
  /// \ingroup utility

  /// \treturn \bool
  template <class T, class C = identity>
  struct is
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<std::is_same<T, x>::value>);
  };

  /// \cond
  template<class T>
  struct is<T, identity>
  {
    template<class x>
    using f = number<std::is_same<T, x>::value>;
  };
  /// \endcond
} // namespace jln::mp
