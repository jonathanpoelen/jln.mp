// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/continuation.hpp"
#include "jln/mp/smp/functional/partial_tee.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<partial_tee>();
  test_unary_pack<partial_tee, identity>();

  ut::same<list<seq_0_1_2_3, seq_0_1_2_3, _2, _3>, partial_tee<listify, listify, listify>
    ::f<_0, _1, _2, _3>>();

  ut::same<list<seq_0_1, seq_0_1>, partial_tee<listify, listify, ut::binary>::f<_0, _1>>();
  ut::same<list<seq_0_1, _1>, partial_tee<listify, ut::binary>::f<_0, _1>>();
  ut::same<_0, partial_tee<identity, ut::unary>::f<_0>>();

  test_context<partial_tee<listify>, smp::partial_tee<smp::listify>>()
    .test<list<>>()
    .test<seq_0, _0>()
    ;

  test_context<
    partial_tee<size<inc<>>, size<>, listify>,
    smp::partial_tee<smp::size<smp::inc<>>, smp::size<>, smp::listify>
  >()
    .test<list<_3, _2>, _0, _4>()
    .test<list<_4, _3, _2>, _0, _4, _2>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  using seq_0_to_4 = list<_0, _1, _2, _3, _4>;
  using seq_0_to_5 = list<_0, _1, _2, _3, _4, _5>;

  test_context<
    partial_tee<listify, listify, listify, listify, listify, listify>,
    smp::partial_tee<smp::listify, smp::listify, smp::listify, smp::listify, smp::listify, smp::listify>
  >()
    .test<list<seq_0_to_5, seq_0_to_5, seq_0_to_5, seq_0_to_5, seq_0_to_5, _5>,
      _0, _1, _2, _3, _4, _5>()
    .test<list<seq_0_to_4, seq_0_to_4, seq_0_to_4, seq_0_to_4, seq_0_to_4>,
      _0, _1, _2, _3, _4>()
    .not_invocable<_0, _0, _0, _0>()
    .not_invocable<_0, _0, _0>()
    .not_invocable<_0, _0>()
    .not_invocable<_0>()
    .not_invocable<>()
    ;

  ut::not_invocable<smp::partial_tee<smp::always<na>, smp::listify>>();
  ut::not_invocable<smp::partial_tee<bad_function>>();
  ut::not_invocable<smp::partial_tee<bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee<listify, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee<listify, listify, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee<smp::identity, listify>, _1, _1>();
  ut::not_invocable<smp::partial_tee<smp::identity, smp::identity, listify>, _1, _1>();
  ut::not_invocable<smp::partial_tee<smp::identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee<smp::identity, smp::identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee<>>();
}

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<partial_tee0>();
  test_mulary_pack<partial_tee0, identity>();
  test_mulary_pack<partial_tee0, identity, identity>();
  test_mulary_pack<partial_tee0, identity, identity, identity>();

  ut::same<list<seq_0_1_2_3, seq_0_1_2_3, _2, _3>, partial_tee0<listify, listify, listify>
    ::f<_0, _1, _2, _3>>();

  ut::same<list<seq_0_1, seq_0_1>, partial_tee0<listify, listify, ut::binary>::f<_0, _1>>();
  ut::same<list<seq_0_1, _1>, partial_tee0<listify, ut::binary>::f<_0, _1>>();
  ut::same<_0, partial_tee0<identity, ut::unary>::f<_0>>();

  test_context<partial_tee0<listify>, smp::partial_tee0<smp::listify>>()
    .test<list<>>()
    .test<seq_0, _0>()
    ;

  test_context<
    partial_tee0<listify, listify>,
    smp::partial_tee0<smp::listify, smp::listify>
  >()
    .test<list<list<>>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0_1, _1>, _0, _1>()
    ;

  test_context<
    partial_tee0<listify, listify, listify>,
    smp::partial_tee0<smp::listify, smp::listify, smp::listify>
  >()
    .test<list<seq_0, list<>>, _0>()
    .test<list<seq_0_1, seq_0_1>, _0, _1>()
    .test<list<seq_0_1_2, seq_0_1_2, _2>, _0, _1, _2>()
    .test<list<seq_0_1_2_3, seq_0_1_2_3, _2, _3>, _0, _1, _2, _3>()
    ;

  test_context<
    partial_tee0<listify, listify, listify, listify>,
    smp::partial_tee0<smp::listify, smp::listify, smp::listify, smp::listify>
  >()
    .test<list<seq_0, list<>, list<>>, _0>()
    .test<list<seq_0_1, seq_0_1, list<>>, _0, _1>()
    .test<list<seq_0_1_2, seq_0_1_2, seq_0_1_2>, _0, _1, _2>()
    .test<list<seq_0_1_2_3, seq_0_1_2_3, seq_0_1_2_3, _3>, _0, _1, _2, _3>()
    ;

  test_context<
    partial_tee0<inc<>, listify, listify>,
    smp::partial_tee0<smp::inc<>, smp::listify, smp::listify>
  >()
    .test<list<_1, list<>>, _0>()
    .not_invocable<>()
    .not_invocable<_1, _2>()
    ;

  test_context<
    partial_tee0<size<inc<>>, size<>, listify>,
    smp::partial_tee0<smp::size<smp::inc<>>, smp::size<>, smp::listify>
  >()
    .test<list<_1, _0>>()
    .test<list<_2, _0>, _0>()
    .test<list<_3, _2>, _0, _4>()
    .test<list<_4, _3, _2>, _0, _4, _2>()
    ;

  test_context<
    partial_tee0<size<>, size<>, size<>, size<>, listify>,
    smp::partial_tee0<smp::size<>, smp::size<>, smp::size<>, smp::size<>, smp::listify>
  >()
    .test<list<_3, _3, _3, _0>, _1, _1, _1>()
    .test<list<_4, _4, _4, _4>, _1, _1, _1, _1>()
    .test<list<_6, _6, _6, _6, _1, _3>, _1, _1, _1, _1, _1, _3>()
    ;

  test_context<
    partial_tee0<size<>, size<>, size<>, size<>, size<>, size<>, size<>, size<>, size<>, size<>, listify>,
    smp::partial_tee0<smp::size<>, smp::size<>, smp::size<>, smp::size<>, smp::size<>, smp::size<>, smp::size<>, smp::size<>, smp::size<>, smp::size<>, smp::listify>
  >()
    .test<list<_8, _8, _8, _8, _8, _8, _8, _8, _0, _0>,
      _1, _1, _1, _1, _1, _1, _1, _1>()
    .test<list<_9, _9, _9, _9, _9, _9, _9, _9, _9, _0>,
      _1, _1, _1, _1, _1, _1, _1, _1, _1>()
    .test<list<_10, _10, _10, _10, _10, _10, _10, _10, _10, _10>,
      _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>()
    .test<list<_11, _11, _11, _11, _11, _11, _11, _11, _11, _11, _1>,
      _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>()
    .test<list<_12, _12, _12, _12, _12, _12, _12, _12, _12, _12, _1, _3>,
      _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _3>()
    ;

  ut::not_invocable<smp::partial_tee0<smp::always<na>, smp::listify>>();
  ut::not_invocable<smp::partial_tee0<bad_function>>();
  ut::not_invocable<smp::partial_tee0<bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee0<listify, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee0<listify, listify, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee0<smp::identity, listify>, _1, _1>();
  ut::not_invocable<smp::partial_tee0<smp::identity, smp::identity, listify>, _1, _1>();
  ut::not_invocable<smp::partial_tee0<smp::identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee0<smp::identity, smp::identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee0<>>();
}

TEST_SUITE_END()
