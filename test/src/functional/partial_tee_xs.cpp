// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/functional/partial_tee_xs.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<partial_tee_xs>();
  test_unary_pack<partial_tee_xs, identity>();

  ut::same<list<seq_0_1_2_3, seq_1_2_3>, partial_tee_xs<listify, listify, listify>
    ::f<_0, _1, _2, _3>>();

  ut::same<list<seq_0_1, seq_1>, partial_tee_xs<listify, listify, ut::binary>::f<_0, _1>>();
  ut::same<seq_0_1, partial_tee_xs<listify, ut::unary>::f<_0, _1>>();

  test_context<partial_tee_xs<listify>, smp::partial_tee_xs<smp::listify>>()
    .test<list<>>()
    .not_invocable<_0>()
    ;

  test_context<partial_tee_xs<listify, listify>, smp::partial_tee_xs<smp::listify, smp::listify>>()
    .test<list<list<>>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0_1>, _0, _1>()
    ;

  test_context<
    partial_tee_xs<inc<>, size<>, listify>,
    smp::partial_tee_xs<smp::inc<>, smp::size<>, smp::listify>
  >()
    .test<list<_1, _0>, _0>()
    .not_invocable<list<_3, _1>, _0, _4>()
    .not_invocable<>()
    ;

  test_context<
    partial_tee_xs<size<inc<>>, size<>, listify>,
    smp::partial_tee_xs<smp::size<smp::inc<>>, smp::size<>, smp::listify>
  >()
    .test<list<_2, _0>, _0>()
    .test<list<_3, _1>, _0, _4>()
    .test<list<_4, _2>, _0, _4, _5>()
    .not_invocable<>()
    ;

  using seq_0_to_4 = list<_0, _1, _2, _3, _4>;
  using seq_0_to_5 = list<_0, _1, _2, _3, _4, _5>;

  test_context<
    partial_tee_xs<listify, listify, listify, listify, listify, listify>,
    smp::partial_tee_xs<smp::listify, smp::listify, smp::listify, smp::listify, smp::listify, smp::listify>
  >()
    .test<list<seq_0_to_5, seq_0_to_5, seq_0_to_5, seq_0_to_5, list<_4, _5>>,
      _0, _1, _2, _3, _4, _5>()
    .test<list<seq_0_to_4, seq_0_to_4, seq_0_to_4, seq_0_to_4, seq_4>,
      _0, _1, _2, _3, _4>()
    .test<list<seq_0_1_2_3, seq_0_1_2_3, seq_0_1_2_3, seq_0_1_2_3, list<>>, _0, _1, _2, _3>()
    .not_invocable<_0, _0, _0>()
    .not_invocable<_0, _0>()
    .not_invocable<_0>()
    .not_invocable<>()
    ;

  ut::not_invocable<smp::partial_tee_xs<smp::always<na>, smp::listify>>();
  ut::not_invocable<smp::partial_tee_xs<bad_function>>();
  ut::not_invocable<smp::partial_tee_xs<bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee_xs<listify, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee_xs<listify, listify, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee_xs<smp::identity, listify>, _1, _1>();
  ut::not_invocable<smp::partial_tee_xs<smp::identity, smp::identity, listify>, _1, _1>();
  ut::not_invocable<smp::partial_tee_xs<smp::identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee_xs<smp::identity, smp::identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee_xs<>>();
}

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<partial_tee0_xs>();
  test_mulary_pack<partial_tee0_xs, identity>();
  test_mulary_pack<partial_tee0_xs, identity, identity>();
  test_mulary_pack<partial_tee0_xs, identity, identity, identity>();

  ut::same<list<seq_0_1_2_3, seq_1_2_3>, partial_tee0_xs<listify, listify, listify>
    ::f<_0, _1, _2, _3>>();

  ut::same<list<seq_0_1, seq_1>, partial_tee0_xs<listify, listify, ut::binary>::f<_0, _1>>();
  ut::same<seq_0_1, partial_tee0_xs<listify, ut::unary>::f<_0, _1>>();
  ut::same<_0, partial_tee0_xs<identity, ut::unary>::f<_0>>();

  test_context<partial_tee0_xs<listify>, smp::partial_tee0_xs<smp::listify>>()
    .test<list<>>()
    .not_invocable<_0>()
    ;

  test_context<
    partial_tee0_xs<always<_0>, always<_1>, always<_2>, listify>,
    smp::partial_tee0_xs<smp::always<_0>, smp::always<_1>, smp::always<_2>, smp::listify>
  >()
    .test<list<_0, _1, _2>>()
    .test<list<_0, _1, _2>, _0>()
    .test<list<_0, _1, _2>, _0, _1>()
    .test<list<_0, _1, _2>, _0, _1, _2>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3, _4>()
    ;

  test_context<
    partial_tee0_xs<listify, listify>,
    smp::partial_tee0_xs<smp::listify, smp::listify>
  >()
    .test<list<list<>>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0_1>, _0, _1>()
    .test<list<seq_0_1_2>, _0, _1, _2>()
    ;

  test_context<
    partial_tee0_xs<listify, listify, listify>,
    smp::partial_tee0_xs<smp::listify, smp::listify, smp::listify>
  >()
    .test<list<list<>, list<>>>()
    .test<list<seq_0, list<>>, _0>()
    .test<list<seq_0_1, seq_1>, _0, _1>()
    .test<list<seq_0_1_2, seq_1_2>, _0, _1, _2>()
    .test<list<seq_0_1_2_3, seq_1_2_3>, _0, _1, _2, _3>()
    ;

  using seq_0_to_4 = list<_0, _1, _2, _3, _4>;

  test_context<
    partial_tee0_xs<listify, listify, listify, listify>,
    smp::partial_tee0_xs<smp::listify, smp::listify, smp::listify, smp::listify>
  >()
    .test<list<seq_0, list<>, list<>>, _0>()
    .test<list<seq_0_1, seq_0_1, list<>>, _0, _1>()
    .test<list<seq_0_1_2, seq_0_1_2, seq_2>, _0, _1, _2>()
    .test<list<seq_0_1_2_3, seq_0_1_2_3, seq_2_3>, _0, _1, _2, _3>()
    .test<list<seq_0_to_4, seq_0_to_4, seq_2_3_4>, _0, _1, _2, _3, _4>()
    ;

  test_context<
    partial_tee0_xs<inc<>, dec<>, listify>,
    smp::partial_tee0_xs<smp::inc<>, smp::dec<>, smp::listify>
  >()
    .not_invocable<>()
    .not_invocable<_0>()
    .not_invocable<_0, _1>()
    .not_invocable<_0, _4, _2>()
    .not_invocable<_0, _4, _2, _1>()
    ;

  test_context<
    partial_tee0_xs<size<inc<>>, listify, listify>,
    smp::partial_tee0_xs<smp::size<smp::inc<>>, smp::listify, smp::listify>
  >()
    .test<list<_1, list<>>>()
    .test<list<_2, list<>>, _0>()
    .test<list<_3, seq_4>, _0, _4>()
    .test<list<_4, list<_4, _5>>, _0, _4, _5>()
    ;

  test_context<
    partial_tee0_xs<size<>, size<>, size<>, size<>, listify>,
    smp::partial_tee0_xs<smp::size<>, smp::size<>, smp::size<>, smp::size<>, smp::listify>
  >()
    .test<list<_0, _0, _0, _0>>()
    .test<list<_1, _0, _0, _0>, _1>()
    .test<list<_2, _2, _0, _0>, _1, _1>()
    .test<list<_3, _3, _3, _0>, _1, _1, _1>()
    .test<list<_4, _4, _4, _1>, _1, _1, _1, _1>()
    .test<list<_5, _5, _5, _2>, _1, _1, _1, _1, _1>()
    .test<list<_6, _6, _6, _3>, _1, _1, _1, _1, _1, _3>()
    ;

  test_context<
    partial_tee0_xs<size<>, size<>, size<>, size<>, size<>, size<>, size<>, size<>, size<>, size<>, listify>,
    smp::partial_tee0_xs<smp::size<>, smp::size<>, smp::size<>, smp::size<>, smp::size<>, smp::size<>, smp::size<>, smp::size<>, smp::size<>, smp::size<>, smp::listify>
  >()
    .test<list<_8, _8, _8, _8, _8, _8, _8, _8, _0, _0>,
      _1, _1, _1, _1, _1, _1, _1, _1>()
    .test<list<_9, _9, _9, _9, _9, _9, _9, _9, _9, _0>,
      _1, _1, _1, _1, _1, _1, _1, _1, _1>()
    .test<list<_10, _10, _10, _10, _10, _10, _10, _10, _10, _1>,
      _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>()
    .test<list<_11, _11, _11, _11, _11, _11, _11, _11, _11, _2>,
      _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>()
    .test<list<_12, _12, _12, _12, _12, _12, _12, _12, _12, _3>,
      _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _3>()
    ;

  ut::not_invocable<smp::partial_tee0_xs<smp::always<na>, smp::listify>>();
  ut::not_invocable<smp::partial_tee0_xs<bad_function>>();
  ut::not_invocable<smp::partial_tee0_xs<bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee0_xs<listify, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee0_xs<listify, listify, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee0_xs<smp::identity, listify>, _1, _1>();
  ut::not_invocable<smp::partial_tee0_xs<smp::identity, smp::identity, listify>, _1, _1>();
  ut::not_invocable<smp::partial_tee0_xs<smp::identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee0_xs<smp::identity, smp::identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee0_xs<>>();
}

TEST_SUITE_END()
