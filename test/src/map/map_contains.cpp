// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/map/map_contains.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<map_contains>();

  ut::same<_1, emp::map_contains<list<seq_0, seq_1_0>, _1>>();
  ut::same<_0, emp::map_contains<list<seq_0, seq_1_0>, _2>>();
  ut::same<seq_0, emp::map_contains<list<seq_0, seq_1_0>, _2, listify>>();
  ut::same<seq_1, emp::map_contains<list<seq_0, seq_1_0>, _1, listify>>();

  test_context<map_contains<_0>, smp::map_contains<_0>>()
    .test<_0>()
    .test<_1, seq_0>()
    .test<_1, seq_1, seq_0>()
    .test<_0, seq_1>()
    .test<_1, seq_0_1>()
    .test<_1, seq_1, seq_0_1>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  test_context<map_contains<_2>, smp::map_contains<_2>>()
    .test<_0>()
    .test<_0, seq_0>()
    .test<_0, seq_0, seq_1>()
    .test<_1, seq_0, seq_1, seq_2>()
    .test<_1, seq_0, seq_1, seq_2, seq_3>()
    .test<_0, seq_0, seq_1, seq_3>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  ut::not_invocable<smp::map_contains<_0, bad_function>, seq_0>();


  ut::same<_0, emp::map_not_contains<list<seq_0, seq_1_0>, _1>>();
  ut::same<_1, emp::map_not_contains<list<seq_0, seq_1_0>, _2>>();
  ut::same<seq_1, emp::map_not_contains<list<seq_0, seq_1_0>, _2, listify>>();
  ut::same<seq_0, emp::map_not_contains<list<seq_0, seq_1_0>, _1, listify>>();

  test_context<map_not_contains<_0>, smp::map_not_contains<_0>>()
    .test<_1>()
    .test<_0, seq_0>()
    .test<_0, seq_1, seq_0>()
    .test<_1, seq_1>()
    .test<_0, seq_0_1>()
    .test<_0, seq_1, seq_0_1>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  test_context<map_not_contains<_2>, smp::map_not_contains<_2>>()
    .test<_1>()
    .test<_1, seq_0>()
    .test<_1, seq_0, seq_1>()
    .test<_0, seq_0, seq_1, seq_2>()
    .test<_0, seq_0, seq_1, seq_2, seq_3>()
    .test<_1, seq_0, seq_1, seq_3>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  ut::not_invocable<smp::map_not_contains<_0, bad_function>, seq_0>();
}

TEST_SUITE_END()
