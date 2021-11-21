#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/drop_while.hpp"
#include "jln/mp/smp/utility/is_not.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<drop_while, is<int>>();
  test_pack3<drop_while>();

  test_context<drop_while<is_not<_3>>, smp::drop_while<smp::is_not<_3>>>()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<>, _0, _1>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1, _2, _0, _1, _2, _0, _1>()
    .test<list<>, _0, _1, _2, _0, _1, _2, _0, _1, _2>()
    .test<seq_3, _3>()
    .test<seq_3_2, _3, _2>()
    .test<seq_3, _0, _1, _2, _3>()
    .test<seq_3_2, _0, _1, _2, _3, _2>()
    .test<list<_3, _1, _2, _0, _1>, _0, _1, _2, _3, _1, _2, _0, _1>()
    .test<list<_3, _1, _2, _0, _1, _2>, _0, _1, _2, _3, _1, _2, _0, _1, _2>()
    .test<list<>, JLN_MP_REPEAT_16(_0, JLN_MP_COMMA)>()
    .test<list<_3, JLN_MP_REPEAT_7(_0, JLN_MP_COMMA)>,
          JLN_MP_REPEAT_8(_0, JLN_MP_COMMA), _3, JLN_MP_REPEAT_7(_0, JLN_MP_COMMA)>()
    .test<list<>,  JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _0>()
    .test<seq_3_2, JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _0, _3, _2>()
    .test<seq_3_2, JLN_MP_REPEAT_16(_0, JLN_MP_COMMA), _3, _2>()
    .test<list<>,  JLN_MP_REPEAT_32(_0, JLN_MP_COMMA)>()
    .test<list<>,  JLN_MP_REPEAT_32(_0, JLN_MP_COMMA), _0>()
    .test<seq_3_2, JLN_MP_REPEAT_32(_0, JLN_MP_COMMA), _3, _2>()
    .test<seq_3_2, JLN_MP_REPEAT_32(_0, JLN_MP_COMMA), _0, _3, _2>()
    .test<list<>,  JLN_MP_REPEAT_64(_0, JLN_MP_COMMA)>()
    .test<list<>,  JLN_MP_REPEAT_64(_0, JLN_MP_COMMA), _0>()
    .test<seq_3_2, JLN_MP_REPEAT_64(_0, JLN_MP_COMMA), _3, _2>()
    .test<seq_3_2, JLN_MP_REPEAT_64(_0, JLN_MP_COMMA), _0, _3, _2>()
    ;

  test_context<drop_while<equal_to_c<3>>, smp::drop_while<smp::equal_to_c<3>>>()
    .test<list<>>()
    .test<seq_1, _1>()
    .test<list<_1, void>, _1, void>()
    .test<list<_1, void>, _3, _1, void>()
    .not_invocable<void>()
    .not_invocable<_3, void>()
    .not_invocable<_3, JLN_MP_REPEAT_64(_3, JLN_MP_COMMA), void>()
    ;

  ut::not_invocable<smp::drop_while<is<_3>, bad_function>>();
  ut::not_invocable<smp::drop_while<is<_3>, bad_function>, void>();
  ut::not_invocable<smp::drop_while<is<_3>, void>>();
  ut::not_invocable<smp::drop_while<always<void>>, void>();
  ut::not_invocable<smp::drop_while<void>, void>();
}

TEST_SUITE_END()
