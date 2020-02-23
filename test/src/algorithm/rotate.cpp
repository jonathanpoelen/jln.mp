#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/rotate.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<rotate, _2>();
  test_pack3<rotate>();

  test_context<rotate_c<2>, smp::rotate_c<2>>()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<seq_0_1, _0, _1>()
    .test<emp::numbers<2, 0, 1>, _0, _1, _2>()
    .test<emp::numbers<2, 3, 4, 5, 6, 7, 8, 0, 1>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<emp::numbers<2, 3, 4, 5, 6, 7, 8, 9, 0, 1>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    ;

  test_context<rotate_c<-1>, smp::rotate_c<-1>>()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<seq_0_1, _1, _0>()
    .test<emp::numbers<2, 0, 1>, _0, _1, _2>()
    .test<emp::numbers<8, 0, 1, 2, 3, 4, 5, 6, 7>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<emp::numbers<9, 0, 1, 2, 3, 4, 5, 6, 7, 8>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    ;

  test_context<rotate_c<-2>, smp::rotate_c<-2>>()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<seq_0_1, _0, _1>()
    .test<emp::numbers<1, 2, 0>, _0, _1, _2>()
    .test<emp::numbers<7, 8, 0, 1, 2, 3, 4, 5, 6>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<emp::numbers<8, 9, 0, 1, 2, 3, 4, 5, 6, 7>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    ;

  test_context<rotate_c<7>, smp::rotate_c<7>>()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<seq_0_1, _1, _0>()
    .test<emp::numbers<1, 2, 0>, _0, _1, _2>()
    .test<emp::numbers<7, 8, 0, 1, 2, 3, 4, 5, 6>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<emp::numbers<7, 8, 9, 0, 1, 2, 3, 4, 5, 6>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    ;

  test_context<rotate_c<8>, smp::rotate_c<8>>()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<seq_0_1, _0, _1>()
    .test<emp::numbers<2, 0, 1>, _0, _1, _2>()
    .test<emp::numbers<8, 0, 1, 2, 3, 4, 5, 6, 7>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<emp::numbers<8, 9, 0, 1, 2, 3, 4, 5, 6, 7>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    ;

  test_context<rotate_c<9>, smp::rotate_c<9>>()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<seq_0_1, _1, _0>()
    .test<seq_0_1_2, _0, _1, _2>()
    .test<emp::numbers<9, 0, 1, 2, 3, 4, 5, 6, 7, 8>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .test<emp::numbers<9, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>()
    ;

  test_context<rotate_c<70>, smp::rotate_c<70>>()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<seq_0_1, _0, _1>()
    .test<emp::numbers<1, 2, 0>, _0, _1, _2>()
    .test<emp::numbers<0, 1, 2, 3, 4, 5, 6, 7, 8, 9>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .test<emp::numbers<4, 5, 6, 7, 8, 9, 10, 0, 1, 2, 3>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>()
    .test<list<
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _64, _65, _66, _67, _68, _69>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _64, _65, _66, _67, _68, _69>()
    .test<list<
      _70, _71, JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _64, _65, _66, _67, _68, _69>,
      JLN_MP_XS_64(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
      _64, _65, _66, _67, _68, _69, _70, _71>()
    ;

  ut::not_invocable<smp::rotate<_2, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::rotate<bad_number, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
