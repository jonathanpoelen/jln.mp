#pragma once

#include <jln/mp/smp/list/insert_range.hpp>
#include <jln/mp/list/insert.hpp>

namespace jln::mp::smp
{
  template<int_ i, class x, class C = listify>
  using insert_c = typename detail::smp_insert_range_dispatch2<true>
    ::template f<i, list<x>, C>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(insert, (I), (x), (C, smp::listify), smp::insert_c<I::value, x, C>)
