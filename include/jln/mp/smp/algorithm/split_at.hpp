#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/take.hpp>
#include <jln/mp/smp/list/drop.hpp>
#include <jln/mp/smp/functional/tee.hpp>
#include <jln/mp/algorithm/split_at.hpp>

namespace jln::mp::smp
{
  template<int_ i, class F = listify, class C = listify>
  using split_at_with_c = try_contract<
    mp::split_at_with_c<i, subcontract<F>, assume_binary_list<C>>>;

  template<int_ i, class C = listify>
  using split_at_c = try_contract<mp::split_at_c<i, assume_binary_list<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(split_at, (I), (C, smp::listify), smp::split_at_c<I::value, C>)
JLN_MP_MAKE_REGULAR_SMP3_P(split_at_with,
  (I), (F, smp::listify), (C, smp::listify), smp::split_at_with_c<I::value, F, C>)
