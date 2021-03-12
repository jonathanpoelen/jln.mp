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
  test_pack2<search_index, is<int>>();
  test_pack3<search_index>();

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

  // test_context<search<_3>, smp::search<_3>>()
  //   .test<list<>>()
  //   .not_invocable<void>()
  //   ;

  using start = list<_1, _2>;
  test_context<
    search_index<starts_with<start>>,
    smp::search_index<smp::starts_with<start>>
  >()
    .test<_0>()
    .test<_1, _2>()
    .test<_0, _1, _2, _3>()
    .test<_4, _1, _0, _2, _3>()
    .test<_1, _0, _1, _2, _3>()
    ;

  ut::not_invocable<smp::search<is<_3>, bad_function>>();
  ut::not_invocable<smp::search<is<_3>, bad_function>, void>();
  ut::not_invocable<smp::search<is<_3>, void>>();
  ut::not_invocable<smp::search<always<void>>, void>();
  ut::not_invocable<smp::search<void>, void>();
}

TEST_SUITE_END()
