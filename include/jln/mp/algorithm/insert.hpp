#pragma once

#include "splice.hpp"

namespace jln::mp
{
  template<class i, class x, class C = listify>
  using insert = splice<i, list<x>, C>;

  template<int_ i, class x, class C = listify>
  using insert_c = splice_c<i, list<x>, C>;

  namespace emp
  {
    template<class L, class i, class x, class C = mp::listify>
    using insert = eager<L, mp::insert<i, x, C>>;

    template<class L, int_ i, class x, class C = mp::listify>
    using insert_c = insert<L, number<i>, x, C>;
  }
}
