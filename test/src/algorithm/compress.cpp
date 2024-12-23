// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/compress.hpp"
#include "jln/mp/number/numbers.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<compress, list<>>();
  test_mulary_pack<compress, emp::numbers<1, 1, 0, 1>>();

  using selectors = emp::numbers<0, 1, 0, 1, 1>;
  using result = list<_1, _3, _4>;

  ut::same<result, emp::compress<emp::numbers<0,1,2,3,4>, selectors>>();
  ut::same<result, emp::compress_c<emp::numbers<0,1,2,3,4>, 0, 1, 0, 1, 1>>();

  test_context<compress<selectors>, smp::compress<selectors>>()
    .test<result, _0, _1, _2, _3, _4>()
    .not_invocable<>()
    .not_invocable<_0, _1, _2, _3>()
    .not_invocable<_0, _1, _2, _3, _4, _5>()
    ;

  using selectors2 = emp::numbers<0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1>;
  test_context<compress<selectors2>, smp::compress<selectors2>>()
    .test<list<_1, _3, _4, _6, _7, _8, _10, _14>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14>()
    .not_invocable<>()
    .not_invocable<_0, _1, _2, _3>()
    .not_invocable<_0, _1, _2, _3, _4, _5>()
    .not_invocable<_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13>()
    .not_invocable<_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15>()
    ;

  test_context<compress<seq_0>, smp::compress<seq_0>>()
    .test<list<>, _0>()
    .not_invocable<>()
    .not_invocable<_0, _1>()
    ;

  test_context<compress<seq_1>, smp::compress<seq_1>>()
    .test<seq_0, _0>()
    .not_invocable<>()
    .not_invocable<_0, _1>()
    ;

  test_context<compress<list<>>, smp::compress<list<>>>()
    .test<list<>>()
    .not_invocable<_0>()
    ;

  ut::not_invocable<smp::compress<int>>();
  ut::not_invocable<smp::compress<list<>, bad_function>>();
  ut::not_invocable<smp::compress<seq_0_1, bad_function>, _0, _1>();
  ut::not_invocable<smp::compress<seq_2>, _0>();
}

TEST_SUITE_END()

