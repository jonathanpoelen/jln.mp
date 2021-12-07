#pragma once

#include <jln/mp/list/insert_range.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Inserts an elements at an arbitrary position.
  /// \pre `0 <= i < sizeof...(xs)`
  /// \treturn \sequence
  template<class i, class x, class C = listify>
  using insert = insert_range<i, list<x>, C>;

  template<unsigned i, class x, class C = listify>
  using insert_c = insert_range_c<i, list<x>, C>;

  namespace emp
  {
    template<class L, class i, class x, class C = mp::listify>
    using insert = unpack<L, mp::insert<i, x, C>>;

    template<class L, int_ i, class x, class C = mp::listify>
    using insert_c = unpack<L, mp::insert_c<i, x, C>>;
  }
}
