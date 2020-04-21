#pragma once

#include "insert_range.hpp"

namespace jln::mp
{
  /// \ingroup list

  /// Insert an elements at an arbitrary position.
  /// \pre 0 \<= i \< sizeof...(xs)
  /// \return \sequence
  template<class i, class x, class C = listify>
  using insert = insert_range<i, list<x>, C>;

  template<int_ i, class x, class C = listify>
  using insert_c = insert_range_c<i, list<x>, C>;

  namespace emp
  {
    template<class L, class i, class x, class C = mp::listify>
    using insert = unpack<L, mp::insert<i, x, C>>;

    template<class L, int_ i, class x, class C = mp::listify>
    using insert_c = insert<L, number<i>, x, C>;
  }
}
