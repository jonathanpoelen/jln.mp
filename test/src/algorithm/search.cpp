#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/search.hpp"
#include "jln/mp/smp/algorithm/starts_with.hpp"
#include "jln/mp/smp/utility/is.hpp"
#include "jln/mp/smp/list/size.hpp"
#include "jln/mp/smp/list/front.hpp"
#include "jln/mp/smp/functional/if.hpp"
#include "jln/mp/smp/number/to_bool.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<search, is<int>>();
  test_pack3<search>();
  test_pack2<search_before, is<int>>();
  test_pack3<search_before_extended_by_n>();
  test_pack2<search_before_extended_by_n, _2, is<int>>();
  test_pack3<search_before>();
  test_pack2<partial_search, _1, is<int>>();
  test_pack3<partial_search, _1>();
  test_pack2<partial_search_before, _1, is<int>>();
  test_pack3<partial_search_before, _1>();
  test_pack2<partial_search_before_extended_by_n, _1, _1, is<int>>();
  test_pack3<partial_search_before_extended_by_n, _1, _1>();

  test_context<search<size<is<_3>>>, smp::search<smp::size<smp::is<_3>>>>()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<>, _0, _1>()
    .test<seq_0_1_2, _0, _1, _2>()
    .test<seq_1_2_3, _0, _1, _2, _3>()
    .test<seq_3_2_1, JLN_MP_RXS_7(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<seq_3_2_1, JLN_MP_RXS_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<seq_3_2_1, void, JLN_MP_RXS_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<seq_3_2_1, JLN_MP_RXS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<seq_3_2_1, void, JLN_MP_RXS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<seq_3_2_1, JLN_MP_RXS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<seq_3_2_1, void, JLN_MP_RXS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<seq_3_2_1, JLN_MP_RXS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<seq_3_2_1, void, JLN_MP_RXS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    ;

  test_context<
    search<if_<front<>, add<to_bool<>>>>,
    smp::search<smp::if_<smp::front<>, smp::add<smp::to_bool<>>>>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    .test<seq_1, _1>()
    .test<seq_1, _0, _1>()
    .test<list<_1, _2, _0>, _0, _0, _1, _2, _0>()
    .not_invocable<void>()
    .not_invocable<_1, void>()
    .not_invocable<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), void>()
    ;


  test_context<search_before<size<is<_3>>>, smp::search_before<smp::size<smp::is<_3>>>>()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<>, _0, _1>()
    .test<list<>, _0, _1, _2>()
    .test<seq_0, _0, _1, _2, _3>()
    .test<
      list<JLN_MP_XS_4(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
      JLN_MP_XS_7(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<
      list<JLN_MP_XS_5(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
      JLN_MP_XS_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<
      list<void, _1, _2, _3, _4, _5>,
      void, JLN_MP_XS_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<
      list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<
      list<void, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13>,
      void, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<
      list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14,
           _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26,
           _27, _28, _29>,
      JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<
      list<void, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13,
                 _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24,
                 _25, _26, _27, _28, _29>,
      void, JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    ;

  test_context<
    search_before<if_<front<>, add<to_bool<>>>>,
    smp::search_before<smp::if_<smp::front<>, smp::add<smp::to_bool<>>>>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<>, _1>()
    .test<seq_0, _0, _1>()
    .test<seq_0_0, _0, _0, _1, _2, _0>()
    .not_invocable<void>()
    .not_invocable<_1, void>()
    .not_invocable<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), void>()
    ;


  test_context<
    search_before_extended_by_n<_2, size<is<_3>>>,
    smp::search_before_extended_by_n<_2, smp::size<smp::is<_3>>>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<>, _0, _1>()
    .test<seq_0_1, _0, _1, _2>()
    .test<seq_0_1_2, _0, _1, _2, _3>()
    .test<
      list<JLN_MP_XS_6(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
      JLN_MP_XS_7(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<
      list<JLN_MP_XS_7(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
      JLN_MP_XS_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<
      list<void, _1, _2, _3, _4, _5, _6, _7>,
      void, JLN_MP_XS_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<
      list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15>,
      JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<
      list<void, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15>,
      void, JLN_MP_XS_16(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<
      list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13,
           _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24,
           _25, _26, _27, _28, _29, _30, _31>,
      JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<
      list<void, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13,
                 _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24,
                 _25, _26, _27, _28, _29, _30, _31>,
      void, JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    ;

  test_context<
    search_before_extended_by_n_c<2, size<is<_3>>>,
    smp::search_before_extended_by_n_c<2, smp::size<smp::is<_3>>>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<_0, _1>, _0, _1, _2>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3>()
    ;

  test_context<
    search_before_extended_by_n_c<2, if_<front<>, add<to_bool<>>>>,
    smp::search_before_extended_by_n_c<2, smp::if_<smp::front<>, smp::add<smp::to_bool<>>>>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    .test<seq_1, _1>()
    .test<seq_0_1, _0, _1>()
    .test<list<_0, _0, _1, _2>, _0, _0, _1, _2, _0>()
    .not_invocable<void>()
    .not_invocable<_1, void>()
    .not_invocable<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), void>()
    ;


  test_context<
    partial_search<_3, size<is<_2>>>,
    smp::partial_search<_3, smp::size<smp::is<_2>>>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<>, _0, _1>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1, _2, _3>()
    ;

  test_context<
    partial_search<_2, size<is<_3>>>,
    smp::partial_search<_2, smp::size<smp::is<_3>>>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<>, _0, _1>()
    .test<seq_0_1_2, _0, _1, _2>()
    .test<seq_1_2_3, _0, _1, _2, _3>()
    ;


  test_context<
    partial_search_before<_3, size<is<_2>>>,
    smp::partial_search_before<_3, smp::size<smp::is<_2>>>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<>, _0, _1>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1, _2, _3>()
    ;

  test_context<
    partial_search_before<_2, size<is<_3>>>,
    smp::partial_search_before<_2, smp::size<smp::is<_3>>>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<>, _0, _1>()
    .test<list<>, _0, _1, _2>()
    .test<seq_0, _0, _1, _2, _3>()
    ;


  test_context<
    partial_search_before_extended_by_n_c<3, 2, size<is<_2>>>,
    smp::partial_search_before_extended_by_n_c<3, 2, smp::size<smp::is<_2>>>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<>, _0, _1>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1, _2, _3>()
    ;

  test_context<
    partial_search_before_extended_by_n_c<2, 2, size<is<_3>>>,
    smp::partial_search_before_extended_by_n_c<2, 2, smp::size<smp::is<_3>>>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<>, _0, _1>()
    .test<seq_0_1, _0, _1, _2>()
    .test<seq_0_1_2, _0, _1, _2, _3>()
    ;


  using start = list<_1, _2>;
  test_context<
    search<starts_with<start>>,
    smp::search<smp::starts_with<start>>
  >()
    .test<list<>>()
    .test<list<>, _0, _1>()
    .test<seq_1_2, _0, _1, _2>()
    .test<seq_1_2_3, _0, _1, _2, _3>()
    ;
  test_context<
    search_before<starts_with<start>>,
    smp::search_before<smp::starts_with<start>>
  >()
    .test<list<>>()
    .test<list<>, _0, _1>()
    .test<seq_0, _0, _1, _2>()
    .test<seq_0, _0, _1, _2, _3>()
    ;
  test_context<
    search_before_extended_by_n_c<1, starts_with<start>>,
    smp::search_before_extended_by_n_c<1, smp::starts_with<start>>
  >()
    .test<list<>>()
    .test<list<>, _0, _1>()
    .test<seq_0_1, _0, _1, _2>()
    .test<seq_0_1, _0, _1, _2, _3>()
    ;


  ut::not_invocable<smp::search<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::search<is<_3>, listify, bad_function>>();
  ut::not_invocable<smp::search<is<_3>, bad_function>, void>();
  ut::not_invocable<smp::search<is<_3>, void>>();
  ut::not_invocable<smp::search<always<void>>, void>();
  ut::not_invocable<smp::search<void>, void>();

  ut::not_invocable<smp::search_before<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::search_before<is<_3>, listify, bad_function>>();
  ut::not_invocable<smp::search_before<is<_3>, bad_function>, void>();
  ut::not_invocable<smp::search_before<is<_3>, void>>();
  ut::not_invocable<smp::search_before<always<void>>, void>();
  ut::not_invocable<smp::search_before<void>, void>();

  ut::not_invocable<smp::search_before_extended_by_n<_1, smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::search_before_extended_by_n<is<_3>, void>>();
  ut::not_invocable<smp::search_before_extended_by_n<is<_3>, void>, void>();
  ut::not_invocable<smp::search_before_extended_by_n<_1, is<_3>, listify, bad_function>>();
  ut::not_invocable<smp::search_before_extended_by_n<_1, is<_3>, bad_function>, void>();
  ut::not_invocable<smp::search_before_extended_by_n<_1, is<_3>, void>>();
  ut::not_invocable<smp::search_before_extended_by_n<_1, is<_3>, void>, _3>();
  ut::not_invocable<smp::search_before_extended_by_n<_1, always<void>>, void>();
  ut::not_invocable<smp::search_before_extended_by_n<_1, void>, void>();

  ut::not_invocable<smp::partial_search<_1, smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::partial_search<_1, is<_3>, listify, bad_function>>();
  ut::not_invocable<smp::partial_search<_1, is<_3>, bad_function>, void, void>();
  ut::not_invocable<smp::partial_search<_1, is<_3>, void>>();
  ut::not_invocable<smp::partial_search<_1, always<void>>, void, void>();
  ut::not_invocable<smp::partial_search<_1, void>, void, void>();
  ut::not_invocable<smp::partial_search<void, is<_3>>>();

  ut::not_invocable<smp::partial_search_before<_1, smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::partial_search_before<_1, is<_3>, listify, bad_function>>();
  ut::not_invocable<smp::partial_search_before<_1, is<_3>, bad_function>, void, void>();
  ut::not_invocable<smp::partial_search_before<_1, is<_3>, void>>();
  ut::not_invocable<smp::partial_search_before<_1, always<void>>, void, void>();
  ut::not_invocable<smp::partial_search_before<_1, void>, void, void>();
  ut::not_invocable<smp::partial_search_before<void, is<_3>>>();

  ut::not_invocable<smp::partial_search_before_extended_by_n<_1, _1, smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::partial_search_before_extended_by_n<_1, void, is<_3>>>();
  ut::not_invocable<smp::partial_search_before_extended_by_n<_1, void, is<_3>>, void, void>();
  ut::not_invocable<smp::partial_search_before_extended_by_n<_1, _1, is<_3>, listify, bad_function>>();
  ut::not_invocable<smp::partial_search_before_extended_by_n<_1, _1, is<_3>, bad_function>, void, void>();
  ut::not_invocable<smp::partial_search_before_extended_by_n<_1, _1, is<_3>, void>>();
  ut::not_invocable<smp::partial_search_before_extended_by_n<_1, _1, is<_3>, void>, _3>();
  ut::not_invocable<smp::partial_search_before_extended_by_n<_1, _1, always<void>>, void, void>();
  ut::not_invocable<smp::partial_search_before_extended_by_n<_1, _1, void>, void, void>();
  ut::not_invocable<smp::partial_search_before_extended_by_n<void, _1, is<_3>>>();
}

TEST_SUITE_END()
