#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/take_until_xs.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/utility/is_not.hpp"
#include "jln/mp/smp/list/front.hpp"

TEST_SUITE_BEGIN()

// take_until_xs
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<take_until_xs>();
  test_mulary_pack<take_until_xs, is<int>>();
  test_mulary_pack<take_until_xs, is<int>, identity>();

  test_context<
    take_until_xs<size<less_equal_than_c<3>>>,
    smp::take_until_xs<smp::size<smp::less_equal_than_c<3>>>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<>, _0, _1>()
    .test<list<>, _0, _1, _2>()
    .test<list<_0>, _0, _1, _2, _3>()
    .test<list<_0, _1>, _0, _1, _2, _3, _4>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3, _4, _5>()
    .test<list<_0, _1, _2, _3>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<_0, _1, _2, _3, _4>, _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<list<_0, _1, _2, _3, _4, _5>, _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<list<_0, _1, _2, _3, _4, _5, _6>, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .test<list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17>()
    .test<list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19, _20>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19, _20, _21>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19, _20, _21, _22>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29>,
      JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30>,
      JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31>,
      JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33, _34>()
    .test<list<JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
      JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33, _34, _35>()
    .test<list<JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44,
               _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
               _57, _58, _59, _60, _61>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44,
               _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
               _57, _58, _59, _60, _61, _62>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65>()
    .test<list<JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44,
               _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
               _57, _58, _59, _60, _61, _62, _63>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66>()
    .test<list<JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66, _67>()
    ;

  test_context<
    take_until_xs<size<greater_equal_than_c<3>>, listify, always<void>>,
    smp::take_until_xs<smp::size<smp::greater_equal_than_c<3>>, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<void, _0, _1>()
    .test<list<>, _0, _1, _2>()
    ;

  test_context<
    take_until_xs<front<not_equal_to_c<3>>>,
    smp::take_until_xs<smp::front<smp::not_equal_to_c<3>>>
  >()
    .test<list<>>()
    .test<list<>, _1>()
    .test<list<>, _1, void>()
    .test<list<_3>, _3, _1, void>()
    .not_invocable<void>()
    .not_invocable<_3, void>()
    .not_invocable<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), void>()
    ;

  test_context<
    take_until_xs<identity, mp::listify, mp::always<void>>,
    smp::take_until_xs<smp::identity, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<list<>, _3>()
    .test<void, _0>()
    .not_invocable<_3, _0>()
    ;

  ut::not_invocable<smp::take_until_xs<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::take_until_xs<is<_3>, bad_function>>();
  ut::not_invocable<smp::take_until_xs<is<_3>, bad_function>, void>();
  ut::not_invocable<smp::take_until_xs<is<_3>, void>>();
  ut::not_invocable<smp::take_until_xs<always<void>>, void>();
  ut::not_invocable<smp::take_until_xs<_3>, void>();
  ut::not_invocable<smp::take_until_xs<void>, void>();
}

// take_inclusive_until_xs
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<take_inclusive_until_xs>();
  test_mulary_pack<take_inclusive_until_xs, is<int>>();
  test_mulary_pack<take_inclusive_until_xs, is<int>, identity>();

  test_context<
    take_inclusive_until_xs<size<less_equal_than_c<3>>>,
    smp::take_inclusive_until_xs<smp::size<smp::less_equal_than_c<3>>>
  >()
    .test<list<>>()
    .test<list<_0>, _0>()
    .test<list<_0>, _0, _1>()
    .test<list<_0>, _0, _1, _2>()
    .test<list<_0, _1>, _0, _1, _2, _3>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3, _4>()
    .test<list<_0, _1, _2, _3>, _0, _1, _2, _3, _4, _5>()
    .test<list<_0, _1, _2, _3, _4>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<_0, _1, _2, _3, _4, _5>, _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<list<_0, _1, _2, _3, _4, _5, _6>, _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<list<_0, _1, _2, _3, _4, _5, _6, _7>, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .test<list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17>()
    .test<list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19, _20>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19, _20, _21>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19, _20>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19, _20, _21, _22>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30>,
      JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31>,
      JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32>,
      JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33, _34>()
    .test<list<JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33>,
      JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33, _34, _35>()
    .test<list<JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44,
               _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
               _57, _58, _59, _60, _61, _62>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44,
               _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
               _57, _58, _59, _60, _61, _62, _63>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65>()
    .test<list<JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44,
               _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
               _57, _58, _59, _60, _61, _62, _63, _64>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66>()
    .test<list<JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66, _67>()
    ;

  test_context<
    take_inclusive_until_xs<size<greater_equal_than_c<3>>, listify, always<void>>,
    smp::take_inclusive_until_xs<smp::size<smp::greater_equal_than_c<3>>, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<void, _0, _1>()
    .test<list<_0>, _0, _1, _2>()
    ;

  test_context<
    take_inclusive_until_xs<front<not_equal_to_c<3>>>,
    smp::take_inclusive_until_xs<smp::front<smp::not_equal_to_c<3>>>
  >()
    .test<list<>>()
    .test<list<_1>, _1>()
    .test<list<_1>, _1, void>()
    .test<list<_3, _1>, _3, _1, void>()
    .not_invocable<void>()
    .not_invocable<_3, void>()
    .not_invocable<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), void>()
    ;

  test_context<
    take_inclusive_until_xs<identity, mp::listify, mp::always<void>>,
    smp::take_inclusive_until_xs<smp::identity, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<seq_3, _3>()
    .test<void, _0>()
    .not_invocable<_3, _0>()
    ;

  ut::not_invocable<smp::take_inclusive_until_xs<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::take_inclusive_until_xs<is<_3>, bad_function>>();
  ut::not_invocable<smp::take_inclusive_until_xs<is<_3>, bad_function>, void>();
  ut::not_invocable<smp::take_inclusive_until_xs<is<_3>, void>>();
  ut::not_invocable<smp::take_inclusive_until_xs<always<void>>, void>();
  ut::not_invocable<smp::take_inclusive_until_xs<_3>, void>();
  ut::not_invocable<smp::take_inclusive_until_xs<void>, void>();
}

// partial_take_until_xs
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<partial_take_until_xs, _9>();
  test_mulary_pack<partial_take_until_xs, _9, is<int>>();
  test_mulary_pack<partial_take_until_xs, _9, is<int>, identity>();

  test_context<
    partial_take_until_xs_c<65, size<less_equal_than_c<3>>>,
    smp::partial_take_until_xs_c<65, smp::size<smp::less_equal_than_c<3>>>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<>, _0, _1>()
    .test<list<>, _0, _1, _2>()
    .test<list<_0>, _0, _1, _2, _3>()
    .test<list<_0, _1>, _0, _1, _2, _3, _4>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3, _4, _5>()
    .test<list<_0, _1, _2, _3>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<_0, _1, _2, _3, _4>, _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<list<_0, _1, _2, _3, _4, _5>, _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<list<_0, _1, _2, _3, _4, _5, _6>, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .test<list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17>()
    .test<list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19, _20>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19, _20, _21>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19, _20, _21, _22>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29>,
      JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30>,
      JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31>,
      JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33, _34>()
    .test<list<JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
      JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33, _34, _35>()
    .test<list<JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44,
               _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
               _57, _58, _59, _60, _61>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44,
               _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
               _57, _58, _59, _60, _61, _62>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65>()
    .test<list<JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44,
               _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
               _57, _58, _59, _60, _61, _62, _63>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66>()
    .test<list<JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66, _67>()
    .test<list<JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66, _67, _68>,
               JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66, _67, _68>()
    ;

  test_context<
    partial_take_until_xs_c<4, size<greater_equal_than_c<3>>, listify, always<void>>,
    smp::partial_take_until_xs_c<4, smp::size<smp::greater_equal_than_c<3>>, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<void, _0, _1>()
    .test<list<>, _0, _1, _2>()
    ;

  test_context<
    partial_take_until_xs_c<66, front<not_equal_to_c<3>>>,
    smp::partial_take_until_xs_c<66, smp::front<smp::not_equal_to_c<3>>>
  >()
    .test<list<>>()
    .test<list<>, _1>()
    .test<list<>, _1, void>()
    .test<list<_3>, _3, _1, void>()
    .test<list<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), _3, void>,
               _3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), _3, void>()
    .not_invocable<void>()
    .not_invocable<_3, void>()
    .not_invocable<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), void>()
    ;

  test_context<
    partial_take_until_xs_c<-2, front<not_equal_to_c<3>>>,
    smp::partial_take_until_xs_c<-2, smp::front<smp::not_equal_to_c<3>>>
  >()
    .test<list<>>()
    .test<list<void>, void>()
    .test<seq_3, _3>()
    .test<seq_3_3, _3, _3>()
    .test<list<_3, _3, _3>, _3, _3, _3>()
    .test<list<_3, _3, _3, _3>, _3, _3, _3, _3>()
    .test<list<_3, _3, _3, _1>, _3, _3, _3, _1>()
    .test<list<_3, _3>, _3, _3, _1, _1>()
    .test<list<_3>, _3, _1, _1, _1>()
    .not_invocable<void, void>()
    ;

  test_context<
    partial_take_until_xs_c<2, identity, mp::listify, mp::always<void>>,
    smp::partial_take_until_xs_c<2, smp::identity, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<list<>, _3>()
    .test<void, _0>()
    .not_invocable<_3, _0>()
    ;

  ut::not_invocable<smp::partial_take_until_xs<_1, smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::partial_take_until_xs<is<_3>, bad_function>>();
  ut::not_invocable<smp::partial_take_until_xs<is<_3>, bad_function>, void>();
  ut::not_invocable<smp::partial_take_until_xs<is<_3>, void>>();
  ut::not_invocable<smp::partial_take_until_xs<_3, always<void>>, void>();
  ut::not_invocable<smp::partial_take_until_xs<_3, _3>, void>();
  ut::not_invocable<smp::partial_take_until_xs<_3, void>, void>();
  ut::not_invocable<smp::partial_take_until_xs<void, front<>>>();
}

// partial_take_inclusive_until_xs
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<partial_take_inclusive_until_xs, _9>();
  test_mulary_pack<partial_take_inclusive_until_xs, _9, is<int>>();
  test_mulary_pack<partial_take_inclusive_until_xs, _9, is<int>, identity>();

  test_context<
    partial_take_inclusive_until_xs_c<65, size<less_equal_than_c<3>>>,
    smp::partial_take_inclusive_until_xs_c<65, smp::size<smp::less_equal_than_c<3>>>
  >()
    .test<list<>>()
    .test<list<_0>, _0>()
    .test<list<_0>, _0, _1>()
    .test<list<_0>, _0, _1, _2>()
    .test<list<_0, _1>, _0, _1, _2, _3>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3, _4>()
    .test<list<_0, _1, _2, _3>, _0, _1, _2, _3, _4, _5>()
    .test<list<_0, _1, _2, _3, _4>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<_0, _1, _2, _3, _4, _5>, _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<list<_0, _1, _2, _3, _4, _5, _6>, _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<list<_0, _1, _2, _3, _4, _5, _6, _7>, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .test<list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17>()
    .test<list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19, _20>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19, _20, _21>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19, _20>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _17, _18, _19, _20, _21, _22>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30>,
      JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31>,
      JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33>()
    .test<list<JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32>,
      JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33, _34>()
    .test<list<JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33>,
      JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _33, _34, _35>()
    .test<list<JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44,
               _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
               _57, _58, _59, _60, _61, _62>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44,
               _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
               _57, _58, _59, _60, _61, _62, _63>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65>()
    .test<list<JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
               _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44,
               _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
               _57, _58, _59, _60, _61, _62, _63, _64>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66>()
    .test<list<JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66, _67>()
    .test<list<JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66, _67, _68>,
               JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _65, _66, _67, _68>()
    ;

  test_context<
    partial_take_inclusive_until_xs_c<4, size<greater_equal_than_c<3>>, listify, always<void>>,
    smp::partial_take_inclusive_until_xs_c<4, smp::size<smp::greater_equal_than_c<3>>, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<void, _0, _1>()
    .test<list<_0>, _0, _1, _2>()
    ;

  test_context<
    partial_take_inclusive_until_xs_c<66, front<not_equal_to_c<3>>>,
    smp::partial_take_inclusive_until_xs_c<66, smp::front<smp::not_equal_to_c<3>>>
  >()
    .test<list<>>()
    .test<list<_1>, _1>()
    .test<list<_1>, _1, void>()
    .test<list<_3, _1>, _3, _1, void>()
    .test<list<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), _3, void>,
               _3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), _3, void>()
    .not_invocable<void>()
    .not_invocable<_3, void>()
    .not_invocable<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), void>()
    ;

  test_context<
    partial_take_inclusive_until_xs_c<2, identity, mp::listify, mp::always<void>>,
    smp::partial_take_inclusive_until_xs_c<2, smp::identity, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<seq_3, _3>()
    .test<void, _0>()
    .not_invocable<_3, _0>()
    ;

  ut::not_invocable<smp::partial_take_inclusive_until_xs<_1, smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::partial_take_inclusive_until_xs<is<_3>, bad_function>>();
  ut::not_invocable<smp::partial_take_inclusive_until_xs<is<_3>, bad_function>, void>();
  ut::not_invocable<smp::partial_take_inclusive_until_xs<is<_3>, void>>();
  ut::not_invocable<smp::partial_take_inclusive_until_xs<_3, always<void>>, void>();
  ut::not_invocable<smp::partial_take_inclusive_until_xs<_3, _3>, void>();
  ut::not_invocable<smp::partial_take_inclusive_until_xs<_3, void>, void>();
  ut::not_invocable<smp::partial_take_inclusive_until_xs<void, front<>>>();
}

TEST_SUITE_END()
