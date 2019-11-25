#pragma once

#include "splice.hpp"
#include "../../algorithm/insert.hpp"

namespace jln::mp::smp
{
  template<class i, class x, class C = listify>
  using insert = splice<i, list<x>, C>;

  template<int_ i, class x, class C = listify>
  using insert_c = splice_c<i, list<x>, C>;
}
