// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/drop_while_xs.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/utility/is_not.hpp"
#include "jln/mp/smp/list/front.hpp"
#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

// drop_while_xs
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<drop_while_xs>();
  test_mulary_pack<drop_while_xs, is<int>>();
  test_mulary_pack<drop_while_xs, is<int>, identity>();

  test_context<
    drop_while_xs<size<greater_than_c<3>>>,
    smp::drop_while_xs<smp::size<smp::greater_than_c<3>>>
  >()
    .test<list<>>()
    .test<list<_0>, _0>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<_0, _1, _2>, _0, _1, _2>()
    .test<list<_1, _2, _3>, _0, _1, _2, _3>()
    .test<list<_2, _3, _4>, _0, _1, _2, _3, _4>()
    .test<list<_3, _4, _5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_4, _5, _6>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<_5, _6, _7>, _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<list<_6, _7, _8>, _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<list<_7, _8, _9>, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .test<list<_14, _15, _16>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<_15, _16, _17>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17>()
    .test<list<_16, _17, _18>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18>()
    .test<list<_17, _18, _19>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18, _19>()
    .test<list<_18, _19, _20>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18, _19, _20>()
    .test<list<_19, _20, _21>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18, _19, _20, _21>()
    .test<list<_20, _21, _22>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18, _19, _20, _21, _22>()
    .test<list<_30, _31, _32>, JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<_31, _32, _33>, JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33>()
    .test<list<_32, _33, _34>, JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33, _34>()
    .test<list<_33, _34, _35>, JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33, _34, _35>()
    .test<list<_62, _63, _64>, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<_63, _64, _65>, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65>()
    .test<list<_64, _65, _66>, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66>()
    .test<list<_65, _66, _67>, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66, _67>()
    ;

  test_context<
    drop_while_xs<size<less_than_c<3>>, mp::listify, mp::always<void>>,
    smp::drop_while_xs<smp::size<smp::less_than_c<3>>, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<void, _0, _1>()
    .test<seq_0_1_2, _0, _1, _2>()
    ;

  test_context<
    drop_while_xs<front<equal_to_c<3>>>,
    smp::drop_while_xs<smp::front<smp::equal_to_c<3>>>
  >()
    .test<list<>>()
    .test<seq_1, _1>()
    .test<list<_1, void>, _1, void>()
    .test<list<_1, void>, _3, _1, void>()
    .not_invocable<void>()
    .not_invocable<_3, void>()
    .not_invocable<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), void>()
    ;

  test_context<
    drop_while_xs<identity, mp::listify, mp::always<void>>,
    smp::drop_while_xs<smp::identity, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _3>()
    .test<seq_0, _0>()
    .not_invocable<_0, _1>()
    ;

  ut::not_invocable<smp::drop_while_xs<is<_3>, bad_function>>();
  ut::not_invocable<smp::drop_while_xs<is<_3>, bad_function>, void>();
  ut::not_invocable<smp::drop_while_xs<is<_3>, void>>();
  ut::not_invocable<smp::drop_while_xs<always<void>>, void>();
  ut::not_invocable<smp::drop_while_xs<_3>, void>();
  ut::not_invocable<smp::drop_while_xs<void>, void>();
}

// drop_inclusive_while_xs
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<drop_inclusive_while_xs>();
  test_mulary_pack<drop_inclusive_while_xs, is<int>>();
  test_mulary_pack<drop_inclusive_while_xs, is<int>, identity>();

  test_context<
    drop_inclusive_while_xs<size<greater_than_c<3>>>,
    smp::drop_inclusive_while_xs<smp::size<smp::greater_than_c<3>>>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<_1>, _0, _1>()
    .test<list<_1, _2>, _0, _1, _2>()
    .test<list<_2, _3>, _0, _1, _2, _3>()
    .test<list<_3, _4>, _0, _1, _2, _3, _4>()
    .test<list<_4, _5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_5, _6>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<_6, _7>, _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<list<_7, _8>, _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<list<_8, _9>, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .test<list<_15, _16>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<_16, _17>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17>()
    .test<list<_17, _18>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18>()
    .test<list<_18, _19>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18, _19>()
    .test<list<_19, _20>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18, _19, _20>()
    .test<list<_20, _21>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18, _19, _20, _21>()
    .test<list<_21, _22>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18, _19, _20, _21, _22>()
    .test<list<_31, _32>, JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<_32, _33>, JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33>()
    .test<list<_33, _34>, JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33, _34>()
    .test<list<_34, _35>, JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33, _34, _35>()
    .test<list<_63, _64>, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<_64, _65>, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65>()
    .test<list<_65, _66>, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66>()
    .test<list<_66, _67>, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66, _67>()
    ;

  test_context<
    drop_inclusive_while_xs<size<less_than_c<3>>, mp::listify, mp::always<void>>,
    smp::drop_inclusive_while_xs<smp::size<smp::less_than_c<3>>, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<void, _0, _1>()
    .test<seq_1_2, _0, _1, _2>()
    ;

  test_context<
    drop_inclusive_while_xs<front<equal_to_c<3>>>,
    smp::drop_inclusive_while_xs<smp::front<smp::equal_to_c<3>>>
  >()
    .test<list<>>()
    .test<list<>, _1>()
    .test<list<void>, _1, void>()
    .test<list<void>, _3, _1, void>()
    .not_invocable<void>()
    .not_invocable<_3, void>()
    .not_invocable<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), void>()
    ;

  test_context<
    drop_inclusive_while_xs<identity, mp::listify, mp::always<void>>,
    smp::drop_inclusive_while_xs<smp::identity, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _3>()
    .test<list<>, _0>()
    .not_invocable<_0, _1>()
    ;

  ut::not_invocable<smp::drop_inclusive_while_xs<is<_3>, bad_function>>();
  ut::not_invocable<smp::drop_inclusive_while_xs<is<_3>, bad_function>, void>();
  ut::not_invocable<smp::drop_inclusive_while_xs<is<_3>, void>>();
  ut::not_invocable<smp::drop_inclusive_while_xs<always<void>>, void>();
  ut::not_invocable<smp::drop_inclusive_while_xs<_3>, void>();
  ut::not_invocable<smp::drop_inclusive_while_xs<void>, void>();
}

// partial_drop_while_xs
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<partial_drop_while_xs, _9>();
  test_mulary_pack<partial_drop_while_xs, _9, is<int>>();
  test_mulary_pack<partial_drop_while_xs, _9, is<int>, identity>();

  test_context<
    partial_drop_while_xs_c<65, size<greater_than_c<3>>>,
    smp::partial_drop_while_xs_c<65, smp::size<smp::greater_than_c<3>>>
  >()
    .test<list<>>()
    .test<list<_0>, _0>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<_0, _1, _2>, _0, _1, _2>()
    .test<list<_1, _2, _3>, _0, _1, _2, _3>()
    .test<list<_2, _3, _4>, _0, _1, _2, _3, _4>()
    .test<list<_3, _4, _5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_4, _5, _6>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<_5, _6, _7>, _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<list<_6, _7, _8>, _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<list<_7, _8, _9>, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .test<list<_14, _15, _16>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<_15, _16, _17>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17>()
    .test<list<_16, _17, _18>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18>()
    .test<list<_17, _18, _19>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18, _19>()
    .test<list<_18, _19, _20>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18, _19, _20>()
    .test<list<_19, _20, _21>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18, _19, _20, _21>()
    .test<list<_20, _21, _22>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18, _19, _20, _21, _22>()
    .test<list<_30, _31, _32>, JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<_31, _32, _33>, JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33>()
    .test<list<_32, _33, _34>, JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33, _34>()
    .test<list<_33, _34, _35>, JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33, _34, _35>()
    .test<list<_62, _63, _64>, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<_63, _64, _65>, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65>()
    .test<list<_64, _65, _66>, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66>()
    .test<list<_65, _66, _67>, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66, _67>()
    .test<list<>, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66, _67, _68>()
    ;

  test_context<
    partial_drop_while_xs_c<4, size<less_than_c<3>>, mp::listify, mp::always<void>>,
    smp::partial_drop_while_xs_c<4, smp::size<smp::less_than_c<3>>, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<void, _0, _1>()
    .test<seq_0_1_2, _0, _1, _2>()
    ;

  test_context<
    partial_drop_while_xs_c<66, front<equal_to_c<3>>>,
    smp::partial_drop_while_xs_c<66, smp::front<smp::equal_to_c<3>>>
  >()
    .test<list<>>()
    .test<seq_1, _1>()
    .test<list<_1, void>, _1, void>()
    .test<list<_1, void>, _3, _1, void>()
    .test<list<>, _3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), _3, void>()
    .not_invocable<void>()
    .not_invocable<_3, void>()
    .not_invocable<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), void>()
    ;

  test_context<
    partial_drop_while_xs_c<-2, front<equal_to_c<3>>>,
    smp::partial_drop_while_xs_c<-2, smp::front<smp::equal_to_c<3>>>
  >()
    .test<list<>>()
    .test<list<>, void>()
    .test<list<>, _3>()
    .test<list<>, _3, _3>()
    .test<list<>, _3, _3, _3>()
    .test<list<>, _3, _3, _3, _3>()
    .test<list<>, _3, _3, _3, _1>()
    .test<seq_1_1, _3, _3, _1, _1>()
    .test<seq_1_1_1, _3, _1, _1, _1>()
    .not_invocable<void, void>()
    ;

  test_context<
    partial_drop_while_xs_c<2, identity, mp::listify, mp::always<void>>,
    smp::partial_drop_while_xs_c<2, smp::identity, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _3>()
    .test<seq_0, _0>()
    .not_invocable<_0, _1>()
    ;

  ut::not_invocable<smp::partial_drop_while_xs<_2, smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::partial_drop_while_xs<smp::always<na>, smp::always<na>>>();
  ut::not_invocable<smp::partial_drop_while_xs<is<_3>, bad_function>>();
  ut::not_invocable<smp::partial_drop_while_xs<is<_3>, bad_function>, void>();
  ut::not_invocable<smp::partial_drop_while_xs<is<_3>, void>>();
  ut::not_invocable<smp::partial_drop_while_xs<_3, always<void>>, void>();
  ut::not_invocable<smp::partial_drop_while_xs<_3, _3>, void>();
  ut::not_invocable<smp::partial_drop_while_xs<_3, void>, void>();
  ut::not_invocable<smp::partial_drop_while_xs<void, front<>>>();
}

// partial_drop_inclusive_while_xs
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<partial_drop_inclusive_while_xs, _9>();
  test_mulary_pack<partial_drop_inclusive_while_xs, _9, is<int>>();
  test_mulary_pack<partial_drop_inclusive_while_xs, _9, is<int>, identity>();

  test_context<
    partial_drop_inclusive_while_xs_c<65, size<greater_than_c<3>>>,
    smp::partial_drop_inclusive_while_xs_c<65, smp::size<smp::greater_than_c<3>>>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<_1>, _0, _1>()
    .test<list<_1, _2>, _0, _1, _2>()
    .test<list<_2, _3>, _0, _1, _2, _3>()
    .test<list<_3, _4>, _0, _1, _2, _3, _4>()
    .test<list<_4, _5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_5, _6>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<_6, _7>, _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<list<_7, _8>, _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<list<_8, _9>, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .test<list<_15, _16>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<_16, _17>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17>()
    .test<list<_17, _18>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18>()
    .test<list<_18, _19>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18, _19>()
    .test<list<_19, _20>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18, _19, _20>()
    .test<list<_20, _21>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18, _19, _20, _21>()
    .test<list<_21, _22>, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _17, _18, _19, _20, _21, _22>()
    .test<list<_31, _32>, JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<_32, _33>, JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33>()
    .test<list<_33, _34>, JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33, _34>()
    .test<list<_34, _35>, JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33, _34, _35>()
    .test<list<_63, _64>, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<_64, _65>, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65>()
    .test<list<_65, _66>, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66>()
    .test<list<_66, _67>, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66, _67>()
    .test<list<>, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66, _67, _68>()
    ;

  test_context<
    partial_drop_inclusive_while_xs_c<4, size<less_than_c<3>>, listify, always<void>>,
    smp::partial_drop_inclusive_while_xs_c<4, smp::size<smp::less_than_c<3>>, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<void, _0, _1>()
    .test<seq_1_2, _0, _1, _2>()
    ;

  test_context<
    partial_drop_inclusive_while_xs_c<66, front<equal_to_c<3>>>,
    smp::partial_drop_inclusive_while_xs_c<66, smp::front<smp::equal_to_c<3>>>
  >()
    .test<list<>>()
    .test<list<>, _1>()
    .test<list<void>, _1, void>()
    .test<list<void>, _3, _1, void>()
    .test<list<>, _3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), _3, void>()
    .not_invocable<void>()
    .not_invocable<_3, void>()
    .not_invocable<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), void>()
    ;

  test_context<
    partial_drop_inclusive_while_xs_c<2, identity, mp::listify, mp::always<void>>,
    smp::partial_drop_inclusive_while_xs_c<2, smp::identity, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _3>()
    .test<list<>, _0>()
    .not_invocable<_0, _1>()
    ;

  ut::not_invocable<smp::partial_drop_inclusive_while_xs<_2, smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::partial_drop_inclusive_while_xs<smp::always<na>, smp::always<na>>>();
  ut::not_invocable<smp::partial_drop_inclusive_while_xs<is<_3>, bad_function>>();
  ut::not_invocable<smp::partial_drop_inclusive_while_xs<is<_3>, bad_function>, void>();
  ut::not_invocable<smp::partial_drop_inclusive_while_xs<is<_3>, void>>();
  ut::not_invocable<smp::partial_drop_inclusive_while_xs<_3, always<void>>, void>();
  ut::not_invocable<smp::partial_drop_inclusive_while_xs<_3, _3>, void>();
  ut::not_invocable<smp::partial_drop_inclusive_while_xs<_3, void>, void>();
  ut::not_invocable<smp::partial_drop_inclusive_while_xs<void, front<>>>();
}

TEST_SUITE_END()
