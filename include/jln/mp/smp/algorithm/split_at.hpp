#pragma once

#include "../list/take.hpp"
#include "../list/drop.hpp"
#include "../functional/fork.hpp"
#include "../../algorithm/split_at.hpp"

namespace jln::mp::smp
{
  template<int_ i, class C = listify>
  using split_at_c = try_contract<mp::split_at_c<i, subcontract<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(split_at, (I), (C, smp::listify), smp::split_at_c<I::value, C>)
