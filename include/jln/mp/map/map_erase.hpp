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
    using map_erase = unpack<L, mp::map_erase<Key, C>>;
  }
}
