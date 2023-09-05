// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/set/set_push_back.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<set_push_back, void>();

  test_context<set_push_back<_2>, smp::set_push_back<_2>>()
    .test<seq_2>()
    .test<seq_1_2, _1>()
    .test<seq_0_1_2, _0, _1>()
    .test<seq_0_1_2, _0, _1, _2>()
    .test<seq_1_2_3, _1, _2, _3>()
    .not_invocable<_1, _1>()
    ;

  ut::not_invocable<smp::set_push_back<_1, bad_function>>();
}

TEST_SUITE_END()
