// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/back.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<back>();

  ut::same<_2, emp::back<seq_0_1_2>>();

  test_context<back<>, smp::back<>>()
    .test<_1, _0, _1>()
    .test<_4, _0, _1, _2, _3, _4>()
    .not_invocable<>()
    ;

  ut::not_invocable<smp::back<bad_function>>();
  ut::not_invocable<smp::back<bad_function>, _1>();
}

TEST_SUITE_END()
