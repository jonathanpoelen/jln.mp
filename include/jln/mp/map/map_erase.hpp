// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/list/join.hpp>
#include <jln/mp/map/map_find.hpp>

namespace jln::mp
{
  /// \ingroup map

  /// If the \map contains an element with a key \c Key, removes it.
  /// \pre \c is_map<>
  /// \treturn \map
  template<class Key, class C = listify>
  using map_erase = transform<map_find<Key, always<list<>>, listify>, join<C>>;

  namespace emp
  {
    template<class L, class Key, class C = mp::listify>
    using map_erase = typename detail::_unpack<mp::map_erase<Key, C>, L>::type;
  }
}
