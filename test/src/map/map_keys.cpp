// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/map/map_keys.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<map_keys>();
  test_mulary_pack<map_keys_with>();

  ut::same<seq_0_1, emp::map_keys<list<seq_0, seq_1_0>>>();
  ut::same<list<seq_0, seq_1>, emp::map_keys_with<list<seq_0, seq_1_0>, listify>>();

  test_context<map_keys<>, smp::map_keys<>>()
    .test<list<>>()
    .test<seq_0, seq_0>()
    .test<seq_0_2, seq_0, seq_2_0>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    ;

  ut::not_invocable<smp::map_keys<bad_function>, seq_0>();
  ut::not_invocable<smp::map_keys_with<smp::identity, bad_function>, seq_0>();
}

TEST_SUITE_END()
