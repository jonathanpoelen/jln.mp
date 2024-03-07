// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/any_of.hpp>
#include <jln/mp/utility/is.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a \value is contained in a \list.
  /// \treturn \bool
  template<class x, class C = identity>
  using contains = any_of<is<x>, C>;

  namespace emp
  {
    template<class L, class x, class C = mp::identity>
    using contains = unpack<L, mp::contains<x, C>>;

    template<class L, class x, class C = mp::identity>
    constexpr bool contains_v = unpack<L, mp::contains<x, C>>::value;
  }
}
