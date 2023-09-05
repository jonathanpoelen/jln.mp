// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/set/set_difference.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<set_difference>();

  test_context<set_difference<>, smp::set_difference<>>()
    .test<seq_1_2, seq_1_2>()
    .test<seq_2, seq_1_2, seq_1>()
    .test<list<>, seq_1_2, seq_1_2>()
    .test<list<>, seq_1_2, seq_1_2_3>()
    .test<list<>, seq_1_2, seq_1, seq_2>()
    .test<seq_3, seq_1_2_3, seq_1, seq_2>()
    .test<list<_0, _5, _7, _9>, seq_0_1_2_3_4_5_6_7_8_9, seq_1_2_3, seq_2_4_6_8_10>()
    .not_invocable<>()
    .not_invocable<_1>()
    .not_invocable<seq_1, _1>()
    .not_invocable<seq_1, seq_1_1>()
    ;

  ut::not_invocable<smp::set_difference<bad_function>>();
  ut::not_invocable<smp::set_difference<bad_function>, seq_0>();
}

TEST_SUITE_END()
