// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/replace.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  (void)replace_if<ut::unary, void>();
  (void)replace_if<ut::listify, void>();
  test_mulary_pack<replace_if, is<int>, void>();

  ut::same<emp::numbers<1, 1, 2>, emp::replace_if<seq_0_1_2, is<_0>, _1>>();
  ut::same<emp::numbers<1, 1, 2>, emp::replace<seq_0_1_2, _0, _1>>();

  test_context<
    replace_if<is<_1>, _2>,
    smp::replace_if<smp::is<_1>, _2>
  >()
    .test<list<>>()
    .test<seq_0_0_0, _0, _0, _0>()
    .test<seq_2_2_2, _1, _1, _1>()
    .test<emp::numbers<0, 2, 3>, _0, _1, _3>()
    ;

  test_context<
    replace_if<is<_1>, na>,
    smp::replace_if<smp::is<_1>, na>
  >()
    .test<list<>>()
    .test<seq_0_0_0, _0, _0, _0>()
    .not_invocable<_0, _1, _3>()
    ;

  test_context<replace<_1, _2>, smp::replace<_1, _2>, 0>()
    .test<list<>>()
    .test<seq_0_0_0, _0, _0, _0>()
    .test<seq_2_2_2, _1, _1, _1>()
    .test<emp::numbers<0, 2, 3>, _0, _1, _3>()
    ;

  test_context<replace<_1, na>, smp::replace<_1, na>, 0>()
    .test<list<>>()
    .test<seq_0_0_0, _0, _0, _0>()
    .not_invocable<_0, _1, _3>()
    ;

  ut::not_invocable<smp::replace<void, void, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::replace_if<smp::always<na>, void>, _1, _1, _1>();
  ut::not_invocable<smp::replace_if<always<_1>, void, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::replace_if<bad_function, void>, _1, _1, _1>();
  ut::not_invocable<smp::replace_if<always<void>, void>, _1, _1, _1>();
  ut::not_invocable<smp::replace_if<bad_function, void, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
