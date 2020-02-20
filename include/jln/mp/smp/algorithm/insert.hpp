#pragma once

#include "insert_range.hpp"
#include "../../algorithm/insert.hpp"

namespace jln::mp::smp
{
  template<int_ i, class x, class C = listify>
  using insert_c = insert_range_c<i, list<x>, C>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(insert, (I), (x), (C, smp::listify), smp::insert_c<I::value, x, C>)
