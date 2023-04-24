#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/take_until.hpp"
#include "jln/mp/smp/utility/is_not.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<take_until>();
  test_mulary_pack<take_until, is<int>>();
  test_mulary_pack<take_until, is<int>, identity>();

  test_context<take_until<is<_3>>, smp::take_until<smp::is<_3>>>()
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
    take_until<is<_3>, listify, always<void>>,
    smp::take_until<smp::is<_3>, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<void, _0, _1>()
    .test<seq_0, _0, _3>()
    .test<list<>, _3, _2>()
    ;

  test_context<take_until<not_equal_to_c<3>>, smp::take_until<smp::not_equal_to_c<3>>>()
    .test<list<>>()
    .test<list<>, _1>()
    .test<seq_3, _3>()
    .not_invocable<void>()
    .not_invocable<_3, void>()
    .not_invocable<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), void>()
    ;

  test_context<
    take_while<identity, mp::listify, mp::always<void>>,
    smp::take_while<smp::identity, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _3>()
    .test<list<>, _0>()
    .test<seq_3, _3, _0>()
    .not_invocable<_1, list<>, _0, _3>()
    ;

  ut::not_invocable<smp::take_until<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::take_until<is<_3>, bad_function>>();
  ut::not_invocable<smp::take_until<is<_3>, bad_function>, void>();
  ut::not_invocable<smp::take_until<is<_3>, void>>();
  ut::not_invocable<smp::take_until<always<void>>, void>();
  ut::not_invocable<smp::take_until<void>, void>();
}

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<take_until_extended_by_n, _9>();
  test_mulary_pack<take_until_extended_by_n, _9, is<int>>();
  test_mulary_pack<take_until_extended_by_n, _9, is<int>, identity>();

  test_context<
    take_until_extended_by_n_c<2, is<_3>>,
    smp::take_until_extended_by_n_c<2, smp::is<_3>>
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

  test_context<
    take_until_extended_by_n_c<2, identity, mp::listify, mp::always<void>>,
    smp::take_until_extended_by_n_c<2, smp::identity, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<seq_3, _3>()
    .test<void, _0>()
    .test<seq_3_0, _3, _0>()
    .not_invocable<_0, list<>, _0, _3>()
    ;

  ut::not_invocable<smp::take_until_extended_by_n_c<2, smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::take_until_extended_by_n_c<2, is<_3>, bad_function>>();
  ut::not_invocable<smp::take_until_extended_by_n_c<2, is<_3>, bad_function>, void>();
  ut::not_invocable<smp::take_until_extended_by_n_c<2, is<_3>, void>>();
  ut::not_invocable<smp::take_until_extended_by_n_c<2, always<void>>, void>();
  ut::not_invocable<smp::take_until_extended_by_n_c<2, void>, void>();
}

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<take_inclusive_until>();
  test_mulary_pack<take_inclusive_until, is<int>>();
  test_mulary_pack<take_inclusive_until, is<int>, identity>();

  test_context<take_inclusive_until<is<_3>>, smp::take_inclusive_until<smp::is<_3>>>()
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
    take_inclusive_until<is<_3>, listify, always<void>>,
    smp::take_inclusive_until<smp::is<_3>, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<void, _0, _1>()
    .test<seq_0_3, _0, _3>()
    .test<seq_3, _3, _2>()
    ;

  test_context<
    take_inclusive_until<not_equal_to_c<3>>,
    smp::take_inclusive_until<smp::not_equal_to_c<3>>
  >()
    .test<list<>>()
    .test<list<_1>, _1>()
    .test<seq_3, _3>()
    .not_invocable<void>()
    .not_invocable<_3, void>()
    .not_invocable<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), void>()
    ;

  test_context<
    take_inclusive_until<identity, mp::listify, mp::always<void>>,
    smp::take_inclusive_until<smp::identity, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<seq_3, _3>()
    .test<void, _0>()
    .test<seq_3, _3, _0>()
    .not_invocable<_0, list<>, _0, _3>()
    ;

  ut::not_invocable<smp::take_inclusive_until<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::take_inclusive_until<is<_3>, bad_function>>();
  ut::not_invocable<smp::take_inclusive_until<is<_3>, bad_function>, void>();
  ut::not_invocable<smp::take_inclusive_until<is<_3>, void>>();
  ut::not_invocable<smp::take_inclusive_until<always<void>>, void>();
  ut::not_invocable<smp::take_inclusive_until<void>, void>();
}

TEST_SUITE_END()
