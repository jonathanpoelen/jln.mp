// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/transform_at.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<list<_1, _1, _2>, emp::transform_at<seq_0_1_2, _0, inc<>>>();
  ut::same<list<_0, _2, _2>, emp::transform_at_c<seq_0_1_2, 1, inc<>>>();

  test_context<transform_at_c<0, inc<>>, smp::transform_at_c<0, smp::inc<>>>()
    .test<seq_2, _1>()
    .test<seq_2_2, _1, _2>()
    .test<list<_2, _2, _3>, _1, _2, _3>()
    .not_invocable<>()
    ;

  test_context<transform_at_c<1, inc<>>, smp::transform_at_c<1, smp::inc<>>>()
    .test<seq_1_3, _1, _2>()
    .test<list<_1, _3, _3>, _1, _2, _3>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  test_context<transform_at_c<2, inc<>>, smp::transform_at_c<2, smp::inc<>>>()
    .test<list<_1, _2, _4>, _1, _2, _3>()
    .not_invocable<>()
    .not_invocable<_1>()
    .not_invocable<_1, _2>()
    ;

  ut::not_invocable<smp::transform_at_c<0, smp::always<na>>, _1>();
  ut::not_invocable<smp::transform_at_c<0, bad_function>, _1>();
  ut::not_invocable<smp::transform_at_c<0, identity, bad_function>, _1>();
  ut::not_invocable<smp::transform_at_c<0, bad_function, bad_function>, _1>();
}

TEST_SUITE_END()
