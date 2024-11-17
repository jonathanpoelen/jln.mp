// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/insert_sequence.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Inserts an elements at an arbitrary position.
  /// \treturn \sequence
  template<int_t index, class x, class C = listify>
  using insert_c = insert_sequence_c<index, list<x>, C>;

  template<class index, class x, class C = listify>
  using insert = insert_sequence_c<index::value, list<x>, C>;

  namespace emp
  {
    template<class L, class index, class x, class C = mp::listify>
    using insert = typename detail::_unpack<mp::insert<index, x, C>, L>::type;

    template<class L, int_t index, class x, class C = mp::listify>
    using insert_c = typename detail::_unpack<mp::insert_c<index, x, C>, L>::type;
  }
}
