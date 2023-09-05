// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/intersperse.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<intersperse, int>();

  ut::same<list<>, emp::intersperse<list<>, int>>();
  ut::same<list<_0>, emp::intersperse<seq_0, int>>();
  ut::same<list<_0, int, _1, int, _2>, emp::intersperse<seq_0_1_2, int>>();

  test_context<intersperse<int>, smp::intersperse<int>>()
    .test<list<>>()
    .test<list<_0>, _0>()
    .test<list<_0, int, _1>, _0, _1>()
    .test<list<_0, int, _1, int, _2>, _0, _1, _2>()
    ;

  ut::not_invocable<smp::intersperse<void, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
