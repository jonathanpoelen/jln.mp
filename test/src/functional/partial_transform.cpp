// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/continuation.hpp"
#include "jln/mp/smp/functional/partial_transform.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<partial_transform>();
  test_unary_pack<partial_transform, identity>();

  ut::same<list<seq_0, seq_1, _2, _3>, partial_transform<listify, listify, listify>
    ::f<_0, _1, _2, _3>>();

  ut::same<seq_0_1, partial_transform<identity, identity, ut::binary>::f<_0, _1>>();
  ut::same<seq_0_1, partial_transform<identity, ut::binary>::f<_0, _1>>();

  test_context<partial_transform<listify>, smp::partial_transform<smp::listify>>()
    .test<list<>>()
    .test<seq_0, _0>()
    ;

  test_context<
    partial_transform<inc<>, dec<>, listify>,
    smp::partial_transform<smp::inc<>, smp::dec<>, smp::listify>
  >()
    .test<list<_1, _3>, _0, _4>()
    .test<list<_1, _3, _2>, _0, _4, _2>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  test_context<
    partial_transform<listify, listify, listify, listify, listify, listify>,
    smp::partial_transform<smp::listify, smp::listify, smp::listify, smp::listify, smp::listify, smp::listify>
  >()
    .test<list<seq_0, seq_1, seq_2, seq_3, seq_4, _5>, _0, _1, _2, _3, _4, _5>()
    .test<list<seq_0, seq_1, seq_2, seq_3, seq_4>, _0, _1, _2, _3, _4>()
    .not_invocable<_0, _0, _0, _0>()
    .not_invocable<_0, _0, _0>()
    .not_invocable<_0, _0>()
    .not_invocable<_0>()
    .not_invocable<>()
    ;

  ut::not_invocable<smp::partial_transform<smp::always<na>, smp::listify>>();
  ut::not_invocable<smp::partial_transform<bad_function>>();
  ut::not_invocable<smp::partial_transform<bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_transform<identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_transform<identity, identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_transform<>>();
}

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<partial_transform0>();
  test_mulary_pack<partial_transform0, identity>();
  test_mulary_pack<partial_transform0, identity, identity>();
  test_mulary_pack<partial_transform0, identity, identity, identity>();

  ut::same<list<seq_0, seq_1, _2, _3>, partial_transform0<listify, listify, listify>
    ::f<_0, _1, _2, _3>>();

  ut::same<seq_0_1, partial_transform0<identity, identity, ut::binary>::f<_0, _1>>();

  test_context<partial_transform0<listify>, smp::partial_transform0<smp::listify>>()
    .test<list<>>()
    .test<seq_0, _0>()
    ;

  test_context<
    partial_transform0<listify, listify>,
    smp::partial_transform0<smp::listify, smp::listify>
  >()
    .test<list<list<>>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0, _1>, _0, _1>()
    ;

  test_context<
    partial_transform0<listify, listify, listify>,
    smp::partial_transform0<smp::listify, smp::listify, smp::listify>
  >()
    .test<list<seq_0, list<>>, _0>()
    .test<list<seq_0, seq_1>, _0, _1>()
    .test<list<seq_0, seq_1, _2>, _0, _1, _2>()
    .test<list<seq_0, seq_1, _2, _3>, _0, _1, _2, _3>()
    ;

  test_context<
    partial_transform0<listify, listify, listify, listify>,
    smp::partial_transform0<smp::listify, smp::listify, smp::listify, smp::listify>
  >()
    .test<list<seq_0, list<>, list<>>, _0>()
    .test<list<seq_0, seq_1, list<>>, _0, _1>()
    .test<list<seq_0, seq_1, seq_2>, _0, _1, _2>()
    .test<list<seq_0, seq_1, seq_2, _3>, _0, _1, _2, _3>()
    ;

  test_context<
    partial_transform0<inc<>, dec<>, listify>,
    smp::partial_transform0<smp::inc<>, smp::dec<>, smp::listify>
  >()
    .test<list<_1, _3>, _0, _4>()
    .test<list<_1, _3, _2>, _0, _4, _2>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  test_context<
    partial_transform0<inc<>, inc<>, inc<>, inc<>, listify>,
    smp::partial_transform0<smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::listify>
  >()
    .test<list<_2, _2, _2, _2>, _1, _1, _1, _1>()
    .test<list<_2, _2, _2, _2, _1, _3>, _1, _1, _1, _1, _1, _3>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    .not_invocable<_0, _0, _0>()
    ;

  test_context<
    partial_transform0<inc<>, inc<>, inc<>, inc<>, inc<>, inc<>, inc<>, inc<>, inc<>, inc<>, listify>,
    smp::partial_transform0<smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::listify>
  >()
    .test<list<_2, _2, _2, _2, _2, _2, _2, _2, _2, _2>, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>()
    .test<list<_2, _2, _2, _2, _2, _2, _2, _2, _2, _2, _1>, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>()
    .test<list<_2, _2, _2, _2, _2, _2, _2, _2, _2, _2, _1, _3>, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _3>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    .not_invocable<_0, _0, _0>()
    .not_invocable<_0, _0, _0, _0>()
    .not_invocable<_0, _0, _0, _0, _0>()
    .not_invocable<_0, _0, _0, _0, _0, _0>()
    .not_invocable<_0, _0, _0, _0, _0, _0, _0>()
    .not_invocable<_0, _0, _0, _0, _0, _0, _0, _0>()
    .not_invocable<_0, _0, _0, _0, _0, _0, _0, _0, _0>()
    ;

  ut::not_invocable<smp::partial_transform0<smp::always<na>, smp::listify>>();
  ut::not_invocable<smp::partial_transform0<bad_function>>();
  ut::not_invocable<smp::partial_transform0<bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_transform0<identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_transform0<identity, identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_transform0<>>();
}

TEST_SUITE_END()
