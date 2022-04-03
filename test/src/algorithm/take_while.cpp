#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/take_while.hpp"
#include "jln/mp/smp/utility/is_not.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<take_while, is<int>>();
  test_pack3<take_while>();

  test_context<take_while<is_not<_3>>, smp::take_while<smp::is_not<_3>>>()
    .test<list<>>()
    .test<list<>, _3>()
    .test<list<>, _3, _2>()
    .test<seq_0, _0>()
    .test<seq_0_1, _0, _1>()
    .test<seq_0_1_2, _0, _1, _2>()
    .test<seq_0_1_2, _0, _1, _2, _3>()
    .test<seq_0_1_2, _0, _1, _2, _3, _1, _2, _0, _1>()
    .test<list<_0, _1, _2, _0, _1, _2, _0, _1>, _0, _1, _2, _0, _1, _2, _0, _1>()
    .test<list<_0, _1, _2, _0, _1, _2, _0, _1, _2>, _0, _1, _2, _0, _1, _2, _0, _1, _2>()
    .test<list<JLN_MP_REPEAT_16(_0, JLN_MP_COMMA)>,     JLN_MP_REPEAT_16(_0, JLN_MP_COMMA)>()
    .test<list<JLN_MP_REPEAT_16(_0, JLN_MP_COMMA)>,     JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _3>()
    .test<list<JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _0>, JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _0, _3>()
    .test<list<JLN_MP_REPEAT_16(_0, JLN_MP_COMMA)>,     JLN_MP_REPEAT_16(_0, JLN_MP_COMMA)>()
    .test<list<JLN_MP_REPEAT_16(_0, JLN_MP_COMMA)>,     JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _3>()
    .test<list<JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _0>, JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _0, _3>()
    .test<list<JLN_MP_REPEAT_16(_0, JLN_MP_COMMA)>,     JLN_MP_REPEAT_16(_0, JLN_MP_COMMA)>()
    .test<list<JLN_MP_REPEAT_16(_0, JLN_MP_COMMA)>,     JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _3>()
    .test<list<JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _0>, JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _0, _3>()
    ;

  test_context<
    take_while<is_not<_3>, mp::listify, mp::always<void>>,
    smp::take_while<smp::is_not<_3>, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<void, _0, _1>()
    .test<seq_0, _0, _3>()
    .test<list<>, _3, _2>()
    ;

  test_context<take_while<equal_to_c<3>>, smp::take_while<smp::equal_to_c<3>>>()
    .test<list<>>()
    .test<list<>, _1>()
    .test<seq_3, _3>()
    .not_invocable<void>()
    .not_invocable<_3, void>()
    .not_invocable<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), void>()
    ;

  ut::not_invocable<smp::take_while<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::take_while<is<_3>, bad_function>>();
  ut::not_invocable<smp::take_while<is<_3>, bad_function>, void>();
  ut::not_invocable<smp::take_while<is<_3>, void>>();
  ut::not_invocable<smp::take_while<always<void>>, void>();
  ut::not_invocable<smp::take_while<void>, void>();
}

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<take_while_extended_by_n, _1, is<int>>();
  test_pack3<take_while_extended_by_n, _1>();

  test_context<
    take_while_extended_by_n_c<2, is_not<_3>>,
    smp::take_while_extended_by_n_c<2, smp::is_not<_3>>
  >()
    .test<list<>>()
    .test<seq_3, _3>()
    .test<seq_3_2, _3, _2>()
    .test<seq_3_2, _3, _2, _1>()
    .test<seq_4_3_2, _4, _3, _2, _1>()
    .test<seq_0, _0>()
    .test<seq_0_1, _0, _1>()
    .test<seq_0_1_2, _0, _1, _2>()
    .test<seq_0_1_2_3, _0, _1, _2, _3>()
    ;

  ut::not_invocable<smp::take_while_extended_by_n_c<2, smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::take_while_extended_by_n_c<2, is_not<_3>, bad_function>>();
  ut::not_invocable<smp::take_while_extended_by_n_c<2, is_not<_3>, bad_function>, void>();
  ut::not_invocable<smp::take_while_extended_by_n_c<2, is_not<_3>, void>>();
  ut::not_invocable<smp::take_while_extended_by_n_c<2, always<void>>, void>();
  ut::not_invocable<smp::take_while_extended_by_n_c<2, void>, void>();
}

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<take_inclusive_while, is<int>>();
  test_pack3<take_inclusive_while>();

  test_context<take_inclusive_while<is_not<_3>>, smp::take_inclusive_while<smp::is_not<_3>>>()
    .test<list<>>()
    .test<seq_3, _3>()
    .test<seq_3, _3, _2>()
    .test<seq_0, _0>()
    .test<seq_0_1, _0, _1>()
    .test<seq_0_1_2, _0, _1, _2>()
    .test<seq_0_1_2_3, _0, _1, _2, _3>()
    .test<seq_0_1_2_3, _0, _1, _2, _3, _1, _2, _0, _1>()
    .test<list<_0, _1, _2, _0, _1, _2, _0, _1>, _0, _1, _2, _0, _1, _2, _0, _1>()
    .test<list<_0, _1, _2, _0, _1, _2, _0, _1, _2>, _0, _1, _2, _0, _1, _2, _0, _1, _2>()
    .test<list<JLN_MP_REPEAT_16(_0, JLN_MP_COMMA)>,         JLN_MP_REPEAT_16(_0, JLN_MP_COMMA)>()
    .test<list<JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _3>,     JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _3>()
    .test<list<JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _0, _3>, JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _0, _3>()
    .test<list<JLN_MP_REPEAT_16(_0, JLN_MP_COMMA)>,         JLN_MP_REPEAT_16(_0, JLN_MP_COMMA)>()
    .test<list<JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _3>,     JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _3>()
    .test<list<JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _0, _3>, JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _0, _3>()
    .test<list<JLN_MP_REPEAT_16(_0, JLN_MP_COMMA)>,         JLN_MP_REPEAT_16(_0, JLN_MP_COMMA)>()
    .test<list<JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _3>,     JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _3>()
    .test<list<JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _0, _3>, JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _0, _3>()
    ;

  test_context<
    take_inclusive_while<is_not<_3>, mp::listify, mp::always<void>>,
    smp::take_inclusive_while<smp::is_not<_3>, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<void, _0, _1>()
    .test<seq_0_3, _0, _3>()
    .test<seq_3, _3, _2>()
    ;

  test_context<take_inclusive_while<equal_to_c<3>>, smp::take_inclusive_while<smp::equal_to_c<3>>>()
    .test<list<>>()
    .test<list<_1>, _1>()
    .test<seq_3, _3>()
    .not_invocable<void>()
    .not_invocable<_3, void>()
    .not_invocable<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), void>()
    ;

  ut::not_invocable<smp::take_inclusive_while<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::take_inclusive_while<is<_3>, bad_function>>();
  ut::not_invocable<smp::take_inclusive_while<is<_3>, bad_function>, void>();
  ut::not_invocable<smp::take_inclusive_while<is<_3>, void>>();
  ut::not_invocable<smp::take_inclusive_while<always<void>>, void>();
  ut::not_invocable<smp::take_inclusive_while<void>, void>();
}

TEST_SUITE_END()
