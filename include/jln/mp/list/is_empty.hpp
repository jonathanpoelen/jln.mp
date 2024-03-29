// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/size.hpp>
#include <jln/mp/number/not.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Checks whether a sequence has no elements.
  /// \treturn \bool
  template<class C = identity>
  using is_empty = size<not_<C>>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using is_empty = unpack<L, mp::is_empty<C>>;

    template<class L, class C = mp::identity>
    constexpr bool is_empty_v = unpack<L, mp::is_empty<C>>::value;
  }
}
