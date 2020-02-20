#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/drop.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<drop, _2>();
  test_pack3<drop>();

  test_context<drop_c<2>, smp::drop_c<2>>()
    .test<list<>, _0, _1>()
    .test<seq_2, _0, _1, _2>()
    .test<seq_2_3, _0, _1, _2, _3>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  test_context<drop_c<7>, smp::drop_c<7>>()
    .test<list<>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<_7>, _0, _1, _2, _3, _4, _5, _6, _7>()
    .not_invocable<_0, _1, _2, _3, _4, _5>()
    ;

  test_context<drop_c<8>, smp::drop_c<8>>()
    .test<list<>, _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<list<_8>, _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .not_invocable<_0, _1, _2, _3, _4, _5, _6>()
    ;

  test_context<drop_c<9>, smp::drop_c<9>>()
    .test<list<>, _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<list<_9>, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .not_invocable<_0, _1, _2, _3, _4, _5, _6, _7>()
    ;

  test_context<drop_c<9, inc<>>, smp::drop_c<9, smp::inc<>>>()
    .test<_10, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .not_invocable<_0, _1, _2, _3, _4, _5, _6, _7, _8>()
    ;

  test_context<drop_c<70>, smp::drop_c<70>>()
    .test<list<>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _64, _65, _66, _67, _68, _69>()
    .test<list<_70, _71>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _64, _65, _66, _67, _68, _69, _70, _71>()
    .not_invocable<
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _64, _65, _66, _67, _68>()
    ;

  test_context<drop_c<70, inc<>>, smp::drop_c<70, smp::inc<>>>()
    .test<_71,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _64, _65, _66, _67, _68, _69, _70>()
    .not_invocable<
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _64, _65, _66, _67, _68, _69>()
    ;
}

TEST_SUITE_END()
