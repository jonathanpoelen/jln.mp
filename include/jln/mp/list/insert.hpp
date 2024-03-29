// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/insert_sequence.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Inserts an elements at an arbitrary position.
  /// \treturn \sequence
  template<int_ index, class x, class C = listify>
  using insert_c = insert_sequence_c<index, list<x>, C>;

  template<class index, class x, class C = listify>
  using insert = insert_sequence_c<index::value, list<x>, C>;

  namespace emp
  {
    template<class L, class index, class x, class C = mp::listify>
    using insert = unpack<L, mp::insert<index, x, C>>;

    template<class L, int_ index, class x, class C = mp::listify>
    using insert_c = unpack<L, mp::insert_c<index, x, C>>;
  }
}
