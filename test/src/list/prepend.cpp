// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/prepend.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<prepend, list<>>();

  ut::same<list<_3, _4, _0, _1, _2>, emp::prepend<seq_0_1_2, _3, _4>>();

  test_context<prepend<list<_9>>, smp::prepend<list<_9>>>()
    .test<list<_9>>()
    .test<list<_0, _1, _2, _9>, _0, _1, _2>()
    ;

  ut::not_invocable<smp::prepend<_1>>();
  ut::not_invocable<smp::prepend<list<>, bad_function>>();
}

TEST_SUITE_END()
