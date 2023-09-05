// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/until_last.hpp"
#include "jln/mp/smp/algorithm/find.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<emp::until_last<seq_2_1, find<_1>>, seq_1>();

  test_context<until_last<find<_1>>, smp::until_last<smp::find<_1>>, 0>()
    .test<list<>, _0, _0, _0>()
    .test<seq_1, _1, _1, _1>()
    .test<seq_1_2_3, _1, _4, _3, _1, _2, _3>()
  ;

  ut::not_invocable<smp::until_last<int>>();
}

TEST_SUITE_END()
