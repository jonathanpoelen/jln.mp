#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/take_while.hpp"
#include "jln/mp/smp/utility/is.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<take_while, is<int>>();
  test_pack3<take_while>();

  test_context<take_while<is<_3, not_<>>>, smp::take_while<smp::is<_3, smp::not_<>>>>()
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

  test_context<take_while<equal_to_c<3>>, smp::take_while<smp::equal_to_c<3>>>()
    .test<list<>>()
    .test<list<>, _1>()
    .test<seq_3, _3>()
    .not_invocable<void>()
    .not_invocable<_3, void>()
    .not_invocable<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), void>()
    ;

  // test_context<take_while<_3>, smp::take_while<_3>>()
  //   .test<list<>>()
  //   .not_invocable<void>()
  //   ;

  ut::not_invocable<smp::take_while<is<_3>, bad_function>>();
  ut::not_invocable<smp::take_while<is<_3>, bad_function>, void>();
  ut::not_invocable<smp::take_while<is<_3>, void>>();
  ut::not_invocable<smp::take_while<always<void>>, void>();
  ut::not_invocable<smp::take_while<void>, void>();
}

TEST_SUITE_END()
