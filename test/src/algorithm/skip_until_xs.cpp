#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/skip_until_xs.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/utility/is_not.hpp"
#include "jln/mp/smp/list/front.hpp"
#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

// skip_until_xs
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<skip_until_xs>();
  test_mulary_pack<skip_until_xs, is<int>>();
  test_mulary_pack<skip_until_xs, is<int>, identity>();

  test_context<
    skip_until_xs<size<less_equal_than_c<3>>>,
    smp::skip_until_xs<smp::size<smp::less_equal_than_c<3>>>
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
    skip_until_xs<front<not_equal_to_c<3>>>,
    smp::skip_until_xs<smp::front<smp::not_equal_to_c<3>>>
  >()
    .test<list<>>()
    .test<seq_1, _1>()
    .test<list<_1, void>, _1, void>()
    .test<list<_1, void>, _3, _1, void>()
    .not_invocable<void>()
    .not_invocable<_3, void>()
    .not_invocable<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), void>()
    ;

  test_context<skip_until_xs<identity>, smp::skip_until_xs<smp::identity>>()
    .test<list<>>()
    .test<list<>, _0>()
    .test<seq_3, _3>()
    .not_invocable<_3, _0>()
    ;

  ut::not_invocable<smp::skip_until_xs<is_not<_3>, bad_function>>();
  ut::not_invocable<smp::skip_until_xs<is_not<_3>, bad_function>, void>();
  ut::not_invocable<smp::skip_until_xs<is_not<_3>, void>>();
  ut::not_invocable<smp::skip_until_xs<always<void>>, void>();
  ut::not_invocable<smp::skip_until_xs<_3>, void>();
  ut::not_invocable<smp::skip_until_xs<void>, void>();
}

// skip_inclusive_until_xs
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<skip_inclusive_until_xs>();
  test_mulary_pack<skip_inclusive_until_xs, is<int>>();
  test_mulary_pack<skip_inclusive_until_xs, is<int>, identity>();

  test_context<
    skip_inclusive_until_xs<size<less_equal_than_c<3>>>,
    smp::skip_inclusive_until_xs<smp::size<smp::less_equal_than_c<3>>>
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
    skip_inclusive_until_xs<front<not_equal_to_c<3>>>,
    smp::skip_inclusive_until_xs<smp::front<smp::not_equal_to_c<3>>>
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
    skip_inclusive_until_xs<identity>,
    smp::skip_inclusive_until_xs<smp::identity>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<>, _3>()
    .not_invocable<_3, _0>()
    ;

  ut::not_invocable<smp::skip_inclusive_until_xs<is_not<_3>, bad_function>>();
  ut::not_invocable<smp::skip_inclusive_until_xs<is_not<_3>, bad_function>, void>();
  ut::not_invocable<smp::skip_inclusive_until_xs<is_not<_3>, void>>();
  ut::not_invocable<smp::skip_inclusive_until_xs<always<void>>, void>();
  ut::not_invocable<smp::skip_inclusive_until_xs<_3>, void>();
  ut::not_invocable<smp::skip_inclusive_until_xs<void>, void>();
}

// partial_skip_until_xs
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<partial_skip_until_xs, _9>();
  test_mulary_pack<partial_skip_until_xs, _9, is<int>>();
  test_mulary_pack<partial_skip_until_xs, _9, is<int>, identity>();

  test_context<
    partial_skip_until_xs_c<65, size<less_equal_than_c<3>>>,
    smp::partial_skip_until_xs_c<65, smp::size<smp::less_equal_than_c<3>>>
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
    partial_skip_until_xs_c<66, front<not_equal_to_c<3>>>,
    smp::partial_skip_until_xs_c<66, smp::front<smp::not_equal_to_c<3>>>
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
    partial_skip_until_xs_c<2, identity>,
    smp::partial_skip_until_xs_c<2, smp::identity>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    .test<seq_3, _3>()
    .not_invocable<_3, _0>()
    ;

  ut::not_invocable<smp::partial_skip_until_xs<_2, smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::partial_skip_until_xs<smp::always<na>, smp::always<na>>>();
  ut::not_invocable<smp::partial_skip_until_xs<is_not<_3>, bad_function>>();
  ut::not_invocable<smp::partial_skip_until_xs<is_not<_3>, bad_function>, void>();
  ut::not_invocable<smp::partial_skip_until_xs<is_not<_3>, void>>();
  ut::not_invocable<smp::partial_skip_until_xs<_3, always<void>>, void>();
  ut::not_invocable<smp::partial_skip_until_xs<_3, _3>, void>();
  ut::not_invocable<smp::partial_skip_until_xs<_3, void>, void>();
  ut::not_invocable<smp::partial_skip_until_xs<void, front<>>>();
}

// partial_skip_inclusive_until_xs
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<partial_skip_inclusive_until_xs, _9>();
  test_mulary_pack<partial_skip_inclusive_until_xs, _9, is<int>>();
  test_mulary_pack<partial_skip_inclusive_until_xs, _9, is<int>, identity>();

  test_context<
    partial_skip_inclusive_until_xs_c<65, size<less_equal_than_c<3>>>,
    smp::partial_skip_inclusive_until_xs_c<65, smp::size<smp::less_equal_than_c<3>>>
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
    partial_skip_inclusive_until_xs_c<66, front<not_equal_to_c<3>>>,
    smp::partial_skip_inclusive_until_xs_c<66, smp::front<smp::not_equal_to_c<3>>>
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
    partial_skip_inclusive_until_xs_c<2, identity, mp::listify, mp::always<void>>,
    smp::partial_skip_inclusive_until_xs_c<2, smp::identity, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<list<>, _3>()
    .not_invocable<_3, _0>()
    ;

  ut::not_invocable<smp::partial_skip_inclusive_until_xs<_2, smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::partial_skip_inclusive_until_xs<smp::always<na>, smp::always<na>>>();
  ut::not_invocable<smp::partial_skip_inclusive_until_xs<is_not<_3>, bad_function>>();
  ut::not_invocable<smp::partial_skip_inclusive_until_xs<is_not<_3>, bad_function>, void>();
  ut::not_invocable<smp::partial_skip_inclusive_until_xs<is_not<_3>, void>>();
  ut::not_invocable<smp::partial_skip_inclusive_until_xs<_3, always<void>>, void>();
  ut::not_invocable<smp::partial_skip_inclusive_until_xs<_3, _3>, void>();
  ut::not_invocable<smp::partial_skip_inclusive_until_xs<_3, void>, void>();
  ut::not_invocable<smp::partial_skip_inclusive_until_xs<void, front<>>>();
}

TEST_SUITE_END()
