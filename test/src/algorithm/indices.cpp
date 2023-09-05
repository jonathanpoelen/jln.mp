// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/indices.hpp"
#include "jln/mp/smp/utility/always.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<seq_0_1_2, emp::indices<seq_0_1_2>>();
  ut::same<seq_0_1_2, emp::indices<seq_1_2_3>>();

  test_mulary_pack<indices>();

  ut::invocable<smp::indices<>>();
  ut::invocable<smp::indices<>, _1>();

  test_context<indices<>, smp::indices<>>()
    .test<list<>>()
    .test<seq_0_1_2, _0, _0, _0>()
    ;

  ut::not_invocable<smp::indices<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::indices<bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
