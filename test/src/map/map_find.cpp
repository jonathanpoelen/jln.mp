// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/map/map_find.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<map_find>();
  test_mulary_pack<map_find, identity>();
  test_mulary_pack<map_find, identity, listify>();

  ut::same<seq_1_0, emp::map_find<list<seq_0, seq_1_0>, _1>>();
  ut::same<void, emp::map_find<list<seq_0, seq_1_0>, _2>>();
  ut::same<list<seq_0, seq_1_0>, emp::map_find<list<seq_0, seq_1_0>, _2, identity, listify>>();
  ut::same<list<seq_1_0>, emp::map_find<list<seq_0, seq_1_0>, _1, listify>>();

  test_context<map_find<_0>, smp::map_find<_0>>()
    .test<void>()
    .test<seq_0, seq_0>()
    .test<seq_0, seq_1, seq_0>()
    .test<void, seq_1>()
    .test<seq_0_1, seq_0_1>()
    .test<seq_0_1, seq_1, seq_0_1>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  test_context<map_find<_2>, smp::map_find<_2>>()
    .test<void>()
    .test<void, seq_0>()
    .test<void, seq_0, seq_1>()
    .test<seq_2, seq_0, seq_1, seq_2>()
    .test<seq_2, seq_0, seq_1, seq_2, seq_3>()
    .test<void, seq_0, seq_1, seq_3>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  ut::not_invocable<smp::map_find<_0, bad_function>, seq_0>();
  ut::not_invocable<smp::map_find<_0, identity, bad_function>>();
}

TEST_SUITE_END()
