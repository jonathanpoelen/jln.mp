#pragma once

#include "../list/join.hpp"
#include "../list/take.hpp"
#include "../list/drop.hpp"
#include "../utility/always.hpp"
#include "../functional/fork.hpp"
#include "../../algorithm/insert_range.hpp"

namespace jln::mp::smp
{
  template<int_ i, class seq, class C = listify>
  using insert_range_c = detail::sfinae<mp::insert_range_c<i, seq, C>>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(insert_range, (I), (seq), (C, smp::listify),
  smp::insert_range_c<I::value, seq, C>)
