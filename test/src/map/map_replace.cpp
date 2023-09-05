// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/map/map_replace.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<map_replace, seq_0>();

  ut::same<list<seq_0, seq_1_1>, emp::map_replace<list<seq_0, seq_1_0>, seq_1_1>>();
  ut::same<list<seq_0, seq_1_0>, emp::map_replace<list<seq_0, seq_1_0>, seq_2>>();

  test_context<map_replace<seq_2>, smp::map_replace<seq_2>>()
    .test<list<>>()
    .test<list<seq_0>, seq_0>()
    .test<list<seq_0, seq_2>, seq_0, seq_2_0>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  ut::not_invocable<smp::map_replace<_0, bad_function>, seq_0>();
}

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<map_replace_or_insert, seq_0>();

  ut::same<list<seq_0, seq_1_1>, emp::map_replace_or_insert<list<seq_0, seq_1_0>, seq_1_1>>();
  ut::same<list<seq_0, seq_1_0, seq_2>, emp::map_replace_or_insert<list<seq_0, seq_1_0>, seq_2>>();

  test_context<map_replace_or_insert<seq_2>, smp::map_replace_or_insert<seq_2>>()
    .test<list<seq_2>>()
    .test<list<seq_0, seq_2>, seq_0>()
    .test<list<seq_0, seq_2>, seq_0, seq_2_0>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  ut::not_invocable<smp::map_replace_or_insert<_0, bad_function>, seq_0>();
}

TEST_SUITE_END()
