// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/transform_if.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<transform_if, inc<>>();
  test_unary_pack<transform_if, inc<>, inc<>>();
  test_mulary_pack<transform_if, inc<>>();
  test_mulary_pack<transform_if, inc<>, inc<>>();

  ut::same<
    list<seq_0, seq_1, _2, _3>,
    emp::transform_if<seq_0_1_2_3, less_than_c<2>, listify>
  >();

  test_context<
    transform_if<less_than_c<2>, listify>,
    smp::transform_if<smp::less_than_c<2>, smp::listify>
  >()
    .test<list<>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0, seq_1>, _0, _1>()
    .test<list<seq_0, seq_1, _2>, _0, _1, _2>()
    .test<list<seq_0, seq_1, _2, _3>, _0, _1, _2, _3>()
    .not_invocable<int>()
    ;

  ut::not_invocable<smp::transform_if<smp::always<true_>, smp::always<na>>, _1>();
  ut::not_invocable<smp::transform_if<smp::always<true_>, bad_function>, _1>();
  ut::not_invocable<smp::transform_if<bad_function, bad_function>, _1>();
  ut::not_invocable<smp::transform_if<bad_function, smp::listify>, _1>();
}

TEST_SUITE_END()
