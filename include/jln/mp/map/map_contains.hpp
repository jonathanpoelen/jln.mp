#pragma once

#include <jln/mp/map/map_find.hpp>

namespace jln::mp
{
  /// \ingroup map

  /// Checks if a key exists in a \map.
  /// \treturn \bool
  /// \pre \c is_map<>
  template<class key, class C = identity>
  using map_contains = map_find<key, always<true_, C>, always<false_, C>>;

  namespace emp
  {
    template<class L, class key, class C = mp::identity>
    using map_contains = unpack<L, mp::map_contains<key, C>>;
  }
}
