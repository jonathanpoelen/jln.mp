#pragma once

#include "insert_range.hpp"

namespace jln::mp
{
  template<class i, class x, class C = listify>
  using insert = insert_range<i, list<x>, C>;

  template<int_ i, class x, class C = listify>
  using insert_c = insert_range_c<i, list<x>, C>;

  namespace emp
  {
    template<class L, class i, class x, class C = mp::listify>
    using insert = eager<L, mp::insert<i, x, C>>;

    template<class L, int_ i, class x, class C = mp::listify>
    using insert_c = insert<L, number<i>, x, C>;
  }
}
