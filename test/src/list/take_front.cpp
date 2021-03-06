#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/take_front.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<take_front, _0>();
  test_pack3<take_front>();

  ut::same<seq_0_1, emp::take_front_c<list<_0, _1, _2, _3>, 2>>();

  test_context<take_front_c<0>, smp::take_front_c<0>>()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<>, _0, _1>()
    ;

  test_context<take_front_c<2>, smp::take_front_c<2>>()
    .test<seq_0_1, _0, _1>()
    .test<seq_0_1, _0, _1, _2>()
    .test<seq_0_1, _0, _1, _2, _3>()
    .not_invocable<_0>()
    ;

  test_context<take_front_c<8>, smp::take_front_c<8>>()
    .test<list<JLN_MP_XS_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
          JLN_MP_XS_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<JLN_MP_XS_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
          JLN_MP_XS_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _0, _0>()
    .not_invocable<_0>()
    .not_invocable<JLN_MP_XS_7(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    ;

  ut::not_invocable<smp::take_front<_1, bad_function>>();
  ut::not_invocable<smp::take_front<_1, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
