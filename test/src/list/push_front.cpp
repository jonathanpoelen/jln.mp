// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/push_front.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<push_front, void>();

  test_context<push_front<_1>, smp::push_front<_1>>()
    .test<seq_1>()
    .test<seq_1_2, _2>()
    .test<seq_1_2_3, _2, _3>()
    ;

  ut::not_invocable<smp::push_front<_1, bad_function>>();
}

TEST_SUITE_END()
