// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/any_of.hpp>
#include <jln/mp/utility/is.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a \value is contained in a \sequence.
  /// \treturn \bool
  template<class x, class C = identity>
  using contains = any_of<is<x>, C>;

  namespace emp
  {
    template<class L, class x, class C = mp::identity>
    using contains = typename detail::_unpack<mp::contains<x, C>, L>::type;

    template<class L, class x, class C = mp::identity>
    inline constexpr bool contains_v = detail::_unpack<mp::contains<x, C>, L>::type::value;
  }
}
