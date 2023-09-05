// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/set/set_push_front_elements.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<set_push_front_elements>();

  test_context<set_push_front_elements<>, smp::set_push_front_elements<>>()
    .test<seq_1_2, seq_1_2>()
    .test<seq_1_2, seq_1_2, _2>()
    .test<seq_0_1_2, seq_1_2, _0>()
    .test<seq_0_1_2_3, seq_2_3, _1, _0>()
    .not_invocable<>()
    .not_invocable<_1>()
    ;

  ut::not_invocable<smp::set_push_front_elements<bad_function>>();
  ut::not_invocable<smp::set_push_front_elements<bad_function>, seq_0>();
}

TEST_SUITE_END()
