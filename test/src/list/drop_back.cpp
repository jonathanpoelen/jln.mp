#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/drop_back.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<drop_back, _2>();
  test_mulary_pack<drop_back_max, _2>();

  test_context<drop_back_c<0>, smp::drop_back_c<0>>()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<seq_0_1, _0, _1>()
    ;

  test_context<drop_back_c<2>, smp::drop_back_c<2>>()
    .test<list<>, _0, _1>()
    .test<seq_0, _0, _1, _2>()
    .test<seq_0_1, _0, _1, _2, _3>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  test_context<drop_back_c<7>, smp::drop_back_c<7>>()
    .test<list<>, _0, _1, _2, _3, _4, _5, _6>()
    .test<seq_0, _0, _1, _2, _3, _4, _5, _6, _7>()
    .not_invocable<_0, _1, _2, _3, _4, _5>()
    ;

  test_context<drop_back_c<8>, smp::drop_back_c<8>>()
    .test<list<>, _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<seq_0, _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .not_invocable<_0, _1, _2, _3, _4, _5, _6>()
    ;

  test_context<drop_back_c<9>, smp::drop_back_c<9>>()
    .test<list<>, _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<seq_0, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .not_invocable<_0, _1, _2, _3, _4, _5, _6, _7>()
    ;

  test_context<drop_back_c<9, inc<>>, smp::drop_back_c<9, smp::inc<>>>()
    .test<_1, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .not_invocable<_0, _1, _2, _3, _4, _5, _6, _7, _8>()
    ;

  test_context<drop_back_c<70>, smp::drop_back_c<70>>()
    .test<list<>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _64, _65, _66, _67, _68, _69>()
    .test<seq_1_2,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _64, _65, _66, _67, _68, _69, _70, _71>()
    .not_invocable<
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _64, _65, _66, _67, _68>()
    ;

  test_context<drop_back_c<70, inc<>>, smp::drop_back_c<70, smp::inc<>>>()
    .test<_2,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _64, _65, _66, _67, _68, _69, _70>()
    .not_invocable<
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _64, _65, _66, _67, _68, _69>()
    ;

  test_context<drop_back_max_c<2>, smp::drop_back_max_c<2>>()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<>, _0, _1>()
    .test<seq_0, _0, _1, _2>()
    ;

  ut::not_invocable<smp::drop_back<smp::always<na>>>();
  ut::not_invocable<smp::drop_back<_1, bad_function>>();
  ut::not_invocable<smp::drop_back<_1, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::drop_back_max<smp::always<na>>>();
  ut::not_invocable<smp::drop_back_max<_1, bad_function>>();
  ut::not_invocable<smp::drop_back_max<_1, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
