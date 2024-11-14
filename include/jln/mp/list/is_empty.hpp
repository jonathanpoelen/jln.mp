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
    using is_empty = typename detail::_unpack<mp::is_empty<C>, L>::type;

    template<class L, class C = mp::identity>
    inline constexpr bool is_empty_v = detail::_unpack<mp::is_empty<C>, L>::type::value;
  }
}
