// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/pairwise.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_binary_pack<pairwise_with>();
  test_mulary_pack<pairwise_with, listify>();

  ut::same<list<>,
    emp::pairwise<seq_0>>();
  ut::same<list<seq_0_1, seq_1_2, seq_2_3>,
    emp::pairwise<seq_0_1_2_3>>();

  test_context<pairwise<>, smp::pairwise<>>()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<seq_0_1>, _0, _1>()
    .test<list<seq_0_1, seq_1_2>, _0, _1, _2>()
    .test<list<seq_0_1, seq_1_2, seq_2_3>, _0, _1, _2, _3>()
    ;

  ut::not_invocable<smp::pairwise<bad_function>>();
  ut::not_invocable<smp::pairwise<bad_function>, _1, _2>();
  ut::not_invocable<smp::pairwise<bad_function>, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>();
}

TEST_SUITE_END()

