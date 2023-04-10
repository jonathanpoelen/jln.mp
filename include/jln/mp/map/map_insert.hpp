#pragma once

#include <jln/mp/list/front.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/map/map_contains.hpp>

namespace jln::mp
{
  /// \ingroup map

  /// Inserts the element \c KV into the map, if the key \c emp::front<KV> does not exist.
  /// \pre \c is_map<>
  /// \treturn \map
  template<class KV, class C = listify>
  using map_insert = if_<map_contains<unpack<front<>>::f<KV>>, C, push_back<KV, C>>;

  namespace emp
  {
    template<class L, class KV, class C = mp::listify>
    using map_insert = unpack<L, mp::map_insert<KV, C>>;
  }
}
