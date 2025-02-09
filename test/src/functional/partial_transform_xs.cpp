// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/continuation.hpp"
#include "jln/mp/smp/functional/partial_transform_xs.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<partial_transform_xs>();
  test_unary_pack<partial_transform_xs, identity>();

  ut::same<list<seq_0, seq_1_2_3>, partial_transform_xs<listify, listify, listify>
    ::f<_0, _1, _2, _3>>();

  ut::same<seq_0_1, partial_transform_xs<identity, identity, ut::binary>::f<_0, _1>>();

  test_context<partial_transform_xs<listify>, smp::partial_transform_xs<smp::listify>>()
    .test<list<>>()
    .not_invocable<_0>()
    ;

  test_context<partial_transform_xs<listify, listify>, smp::partial_transform_xs<smp::listify, smp::listify>>()
    .test<list<list<>>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0_1>, _0, _1>()
    ;

  test_context<
    partial_transform_xs<inc<>, dec<>, listify>,
    smp::partial_transform_xs<smp::inc<>, smp::dec<>, smp::listify>
  >()
    .test<list<_1, _3>, _0, _4>()
    .not_invocable<>()
    .not_invocable<_0>()
    .not_invocable<_0, _4, _2>()
    .not_invocable<void, void>()
    ;

  test_context<
    partial_transform_xs<listify, listify, listify, listify, listify, listify>,
    smp::partial_transform_xs<smp::listify, smp::listify, smp::listify, smp::listify, smp::listify, smp::listify>
  >()
    .test<list<seq_0, seq_1, seq_2, seq_3, list<_4, _5>>, _0, _1, _2, _3, _4, _5>()
    .test<list<seq_0, seq_1, seq_2, seq_3, seq_4>, _0, _1, _2, _3, _4>()
    .test<list<seq_0, seq_1, seq_2, seq_3, list<>>, _0, _1, _2, _3>()
    .not_invocable<_0, _0, _0>()
    .not_invocable<_0, _0>()
    .not_invocable<_0>()
    .not_invocable<>()
    ;

  ut::not_invocable<smp::partial_transform_xs<smp::always<na>, smp::listify>>();
  ut::not_invocable<smp::partial_transform_xs<bad_function>>();
  ut::not_invocable<smp::partial_transform_xs<bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_transform_xs<identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_transform_xs<identity, identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_transform_xs<>>();
}

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<partial_transform0_xs>();
  test_mulary_pack<partial_transform0_xs, identity>();
  test_mulary_pack<partial_transform0_xs, identity, identity>();
  test_mulary_pack<partial_transform0_xs, identity, identity, identity>();

  ut::same<list<seq_0, seq_1_2_3>, partial_transform0_xs<listify, listify, listify>
    ::f<_0, _1, _2, _3>>();

  ut::same<seq_0_1, partial_transform0_xs<identity, identity, ut::binary>::f<_0, _1>>();

  test_context<partial_transform0_xs<listify>, smp::partial_transform0_xs<smp::listify>>()
    .test<list<>>()
    .not_invocable<_0>()
    ;

  test_context<
    partial_transform0_xs<always<_0>, always<_1>, always<_2>, listify>,
    smp::partial_transform0_xs<smp::always<_0>, smp::always<_1>, smp::always<_2>, smp::listify>
  >()
    .test<list<_0, _1, _2>>()
    .test<list<_0, _1, _2>, _0>()
    .test<list<_0, _1, _2>, _0, _1>()
    .test<list<_0, _1, _2>, _0, _1, _2>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3, _4>()
    ;

  test_context<
    partial_transform0_xs<listify, listify>,
    smp::partial_transform0_xs<smp::listify, smp::listify>
  >()
    .test<list<list<>>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0_1>, _0, _1>()
    .test<list<seq_0_1_2>, _0, _1, _2>()
    ;

  test_context<
    partial_transform0_xs<listify, listify, listify>,
    smp::partial_transform0_xs<smp::listify, smp::listify, smp::listify>
  >()
    .test<list<list<>, list<>>>()
    .test<list<seq_0, list<>>, _0>()
    .test<list<seq_0, seq_1>, _0, _1>()
    .test<list<seq_0, seq_1_2>, _0, _1, _2>()
    .test<list<seq_0, seq_1_2_3>, _0, _1, _2, _3>()
    ;

  test_context<
    partial_transform0_xs<listify, listify, listify, listify>,
    smp::partial_transform0_xs<smp::listify, smp::listify, smp::listify, smp::listify>
  >()
    .test<list<seq_0, list<>, list<>>, _0>()
    .test<list<seq_0, seq_1, list<>>, _0, _1>()
    .test<list<seq_0, seq_1, seq_2>, _0, _1, _2>()
    .test<list<seq_0, seq_1, seq_2_3>, _0, _1, _2, _3>()
    .test<list<seq_0, seq_1, seq_2_3_4>, _0, _1, _2, _3, _4>()
    ;

  test_context<
    partial_transform0_xs<inc<>, dec<>, listify>,
    smp::partial_transform0_xs<smp::inc<>, smp::dec<>, smp::listify>
  >()
    .test<list<_1, _3>, _0, _4>()
    .not_invocable<>()
    .not_invocable<_0>()
    .not_invocable<_0, _4, _2>()
    .not_invocable<_0, _4, _2, _1>()
    ;

  test_context<
    partial_transform0_xs<inc<>, inc<>, inc<>, inc<>, listify>,
    smp::partial_transform0_xs<smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::listify>
  >()
    .test<list<_2, _2, _2, _2>, _1, _1, _1, _1>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    .not_invocable<_0, _0, _0>()
    .not_invocable<_1, _1, _1, _1, _1>()
    .not_invocable<_1, _1, _1, _1, _1, _3>()
    ;

  test_context<
    partial_transform0_xs<inc<>, inc<>, inc<>, inc<>, inc<>, inc<>, inc<>, inc<>, inc<>, inc<>, listify>,
    smp::partial_transform0_xs<smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::listify>
  >()
    .test<list<_2, _2, _2, _2, _2, _2, _2, _2, _2, _2>, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    .not_invocable<_0, _0, _0>()
    .not_invocable<_0, _0, _0, _0>()
    .not_invocable<_0, _0, _0, _0, _0>()
    .not_invocable<_0, _0, _0, _0, _0, _0>()
    .not_invocable<_0, _0, _0, _0, _0, _0, _0>()
    .not_invocable<_0, _0, _0, _0, _0, _0, _0, _0>()
    .not_invocable<_0, _0, _0, _0, _0, _0, _0, _0, _0>()
    .not_invocable<_1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>()
    .not_invocable<_1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>()
    ;

  ut::not_invocable<smp::partial_transform0_xs<smp::always<na>, smp::listify>>();
  ut::not_invocable<smp::partial_transform0_xs<bad_function>>();
  ut::not_invocable<smp::partial_transform0_xs<bad_function, bad_function>, _1, _1>();  ut::not_invocable<smp::partial_transform0_xs<identity, bad_function>, _1>();
  ut::not_invocable<smp::partial_transform0_xs<identity, identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_transform0_xs<>>();
}

TEST_SUITE_END()
