// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/transform_third.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

template<class x, class y, class z>
using to = mp::list<x, y, z, void>;

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<transform_third>();
  test_mulary_pack<transform_third, inc<>>();

  ut::same<list<_0, _1, _3>, emp::transform_third<seq_0_1_2, inc<>>>();
  ut::same<list<_0, _1, _3, void>, emp::transform_third<seq_0_1_2, inc<>, lift<to>>>();

  test_context<transform_third<inc<>>, smp::transform_third<smp::inc<>>>()
    .test<list<_0, _1, _3>, _0, _1, _2>()
    .test<list<_0, _1, _3, _4>, _0, _1, _2, _4>()
    .not_invocable<>()
    .not_invocable<_1>()
    .not_invocable<_1, _2>()
    ;

  ut::not_invocable<smp::transform_third<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::transform_third<bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::transform_third<identity, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::transform_third<bad_function, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
