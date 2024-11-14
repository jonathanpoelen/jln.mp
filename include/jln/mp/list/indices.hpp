// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <jln/mp/list/size.hpp>

namespace jln::mp
{
  /// \ingroup number

  /// Replaces each element of a \sequence by its corresponding index.
  /// \treturn \sequence
  template<class C = listify>
  using indices = size<make_int_sequence<C>>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using indices = typename detail::_unpack<mp::indices<C>, L>::type;
  }
} // namespace jln::mp
