// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/uncompress.hpp"
#include "jln/mp/number/numbers.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<uncompress, void, list<>>();
  test_mulary_pack<uncompress, void, emp::numbers<1, 1, 0, 1>>();

  using selectors = emp::numbers<1, 0, 1, 1, 0, 1, 0>;
  using result = list<_0, void, _1, _2, void, _3, void>;

  ut::same<result, emp::uncompress<emp::numbers<0,1,2,3,4>, void, selectors>>();
  ut::same<result, emp::uncompress_c<emp::numbers<0,1,2,3,4>, void, 1, 0, 1, 1, 0, 1, 0>>();

  test_context<uncompress<void, selectors>, smp::uncompress<void, selectors>>()
    .test<result, _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<result, _0, _1, _2, _3, _4, _5>()
    .test<result, _0, _1, _2, _3>()
    .not_invocable<_0, _1, _2>()
    .not_invocable<>()
    ;

  using selectors2 = emp::numbers<0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1>;
  test_context<uncompress<void, selectors2>, smp::uncompress<void, selectors2>>()
    .test<list<void, _0, void, _1, _2, void, _3, _4, _5, void, _6, void, void, void, _7>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14>()
    .test<list<void, _0, void, _1, _2, void, _3, _4, _5, void, _6, void, void, void, _7>,
      _0, _1, _2, _3, _4, _5, _6, _7>()
    .not_invocable<_0, _1, _2, _3, _4, _5, _6>()
    .not_invocable<_0, _1, _2, _3>()
    .not_invocable<>()
    ;

  test_context<uncompress<void, seq_0>, smp::uncompress<void, seq_0>>()
    .test<list<void>>()
    .test<list<void>, _0>()
    .test<list<void>, _0, _1>()
    ;

  test_context<uncompress<void, seq_1>, smp::uncompress<void, seq_1>>()
    .test<seq_0, _0>()
    .test<seq_0, _0, _1>()
    .not_invocable<>()
    ;

  test_context<uncompress<void, list<>>, smp::uncompress<void, list<>>>()
    .test<list<>>()
    .test<list<>, _0>()
    ;

  ut::not_invocable<smp::uncompress<void, int>>();
  ut::not_invocable<smp::uncompress<void, list<>, bad_function>>();
  ut::not_invocable<smp::uncompress<void, seq_0_1, bad_function>, _0, _1>();
  ut::not_invocable<smp::uncompress<void, seq_2>, _0>();
}

TEST_SUITE_END()

