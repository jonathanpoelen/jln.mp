// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/copy.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<copy_if>();
  test_mulary_pack<copy_if, listify>();

  using odd = push_back<number<2>, mod<>>;

  ut::same<seq_1_3_5_7_9, emp::copy_if<seq_0_1_2_3_4_5_6_7_8_9, odd>>();
  ut::same<seq_1, emp::copy<seq_0_1_2, _1>>();

  test_context<copy_if<odd>, smp::copy_if<odd>, 0>()
    .test<list<>>()
    .test<list<>, _0, _0, _0>()
    .test<seq_1_1_1, _1, _1, _1>()
    .test<list<_1, _3>, _0, _1, _2, _3>()
    ;

  test_context<copy_if<always<na>>, smp::copy_if<smp::always<na>>, 0>()
    .test<list<>>()
    .not_invocable<_0>()
    ;

  test_context<copy<_1>, smp::copy<_1>, 0>()
    .test<list<>>()
    .test<list<>, _0, _0, _0>()
    .test<seq_1_1_1, _1, _1, _1>()
    .test<seq_1, _0, _1, _3>()
    ;

  ut::not_invocable<smp::copy<_1, bad_function>>();
  ut::not_invocable<smp::copy<_1, bad_function>>();
  ut::not_invocable<smp::copy<_1, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::copy_if<smp::always<na>>, _1>();
  ut::not_invocable<smp::copy_if<always<void>, bad_function>, _1>();
  ut::not_invocable<smp::copy_if<always<_1>, bad_function>>();
  ut::not_invocable<smp::copy_if<always<_1>, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::copy_if<bad_function, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
