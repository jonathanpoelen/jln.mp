#pragma once

#include "insert_range.hpp"
#include "../../algorithm/insert.hpp"

namespace jln::mp::smp
{
  template<class i, class x, class C = listify>
  using insert = insert_range<i, list<x>, C>;

  template<int_ i, class x, class C = listify>
  using insert_c = insert_range_c<i, list<x>, C>;
}
