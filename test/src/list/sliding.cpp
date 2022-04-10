#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/sliding.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<list<>, emp::sliding<list<>, _3>>();
  ut::same<list<seq_0>, emp::sliding<seq_0, _3>>();
  ut::same<list<seq_0_1>, emp::sliding<seq_0_1, _3>>();
  ut::same<list<seq_0_1_2>, emp::sliding<seq_0_1_2, _3>>();
  ut::same<list<seq_0_1_2, seq_1_2_3>, emp::sliding<seq_0_1_2_3, _3>>();

  ut::same<list<>, emp::sliding_with_stride<list<>, _1, _2>>();
  ut::same<list<seq_0>, emp::sliding_with_stride<seq_0, _1, _2>>();
  ut::same<list<seq_0>, emp::sliding_with_stride<seq_0_1, _1, _2>>();
  ut::same<list<seq_0, seq_2>, emp::sliding_with_stride<seq_0_1_2, _1, _2>>();
  ut::same<list<seq_0, seq_2>, emp::sliding_with_stride<seq_0_1_2_3, _1, _2>>();

  ut::same<list<>, emp::sliding_with_stride<list<>, _2, _2>>();
  ut::same<list<seq_0>, emp::sliding_with_stride<seq_0, _2, _2>>();
  ut::same<list<seq_0_1>, emp::sliding_with_stride<seq_0_1, _2, _2>>();
  ut::same<list<seq_0_1, seq_2>, emp::sliding_with_stride<seq_0_1_2, _2, _2>>();
  ut::same<list<seq_0_1, seq_2_3>, emp::sliding_with_stride<seq_0_1_2_3, _2, _2>>();

  ut::same<list<>, emp::sliding_with_stride<list<>, _3, _2>>();
  ut::same<list<seq_0>, emp::sliding_with_stride<seq_0, _3, _2>>();
  ut::same<list<seq_0_1>, emp::sliding_with_stride<seq_0_1, _3, _2>>();
  ut::same<list<seq_0_1_2>, emp::sliding_with_stride<seq_0_1_2, _3, _2>>();
  ut::same<list<seq_0_1_2, seq_2_3>, emp::sliding_with_stride<seq_0_1_2_3, _3, _2>>();
  ut::same<list<seq_0_1_2, seq_2_3_4>, emp::sliding_with_stride<list<_0, _1, _2, _3, _4>, _3, _2>>();
  ut::same<list<seq_0_1_2, seq_2_3_4, list<_4, _5, _6>>, emp::sliding_with_stride<list<_0, _1, _2, _3, _4, _5, _6>, _3, _2>>();

  test_pack2<sliding_with_stride, _2, _1>();
  test_pack3<sliding_with_stride, void, void>();

  ut::same<list<seq_0_1, seq_1_2>, emp::sliding<seq_0_1_2, _2>>();

  test_context<sliding<_1>, smp::sliding<_1>>()
    .test<list<>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0, seq_1>, _0, _1>()
    .test<list<seq_0, seq_1, seq_2>, _0, _1, _2>()
    ;

  test_context<sliding<_2>, smp::sliding<_2>>()
    .test<list<>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0_1>, _0, _1>()
    .test<list<seq_0_1, seq_1_2>, _0, _1, _2>()
    .test<list<seq_0_1, seq_1_2, seq_2_3>, _0, _1, _2, _3>()
    ;

  test_context<sliding<_3>, smp::sliding<_3>>()
    .test<list<>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0_1>, _0, _1>()
    .test<list<seq_0_1_2>, _0, _1, _2>()
    .test<list<seq_0_1_2, seq_1_2_3>, _0, _1, _2, _3>()
    .test<list<seq_0_1_2, seq_1_2_3, seq_2_3_4>, _0, _1, _2, _3, _4>()
    ;

  test_context<sliding_with_stride<_1, _2>, smp::sliding_with_stride<_1, _2>>()
    .test<list<>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0>, _0, _1>()
    .test<list<seq_0, seq_2>, _0, _1, _2>()
    .test<list<seq_0, seq_2>, _0, _1, _2, _3>()
    ;

  test_context<sliding_with_stride<_2, _2>, smp::sliding_with_stride<_2, _2>>()
    .test<list<>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0_1>, _0, _1>()
    .test<list<seq_0_1, seq_2>, _0, _1, _2>()
    .test<list<seq_0_1, seq_2_3>, _0, _1, _2, _3>()
    ;

  test_context<sliding_with_stride<_3, _2>, smp::sliding_with_stride<_3, _2>>()
    .test<list<>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0_1>, _0, _1>()
    .test<list<seq_0_1_2>, _0, _1, _2>()
    .test<list<seq_0_1_2, seq_2_3>, _0, _1, _2, _3>()
    .test<list<seq_0_1_2, seq_2_3_4>, _0, _1, _2, _3, _4>()
    .test<list<seq_0_1_2, seq_2_3_4, list<_4, _5, _6>>, _0, _1, _2, _3, _4, _5, _6>()
    ;

  test_context<sliding_with_stride<_5, _2>, smp::sliding_with_stride<_5, _2>>()
    .test<list<>>()
    .test<list<seq_0_1_2_3>, _0, _1, _2, _3>()
    .test<list<list<_0, _1, _2, _3, _4>, list<_2, _3, _4, _5>>, _0, _1, _2, _3, _4, _5>()
    .test<list<list<_0, _1, _2, _3, _4>, list<_2, _3, _4, _5, _6>>,
      _0, _1, _2, _3, _4, _5, _6>()
    .test<list<list<_0, _1, _2, _3, _4>, list<_2, _3, _4, _5, _6>, list<_4, _5, _6, _7>>,
      _0, _1, _2, _3, _4, _5, _6, _7>()
    ;

  test_context<sliding_with_stride<_2, _5>, smp::sliding_with_stride<_2, _5>>()
    .test<list<>>()
    .test<list<seq_0_1>, _0, _1, _2, _3>()
    .test<list<seq_0_1>, _0, _1, _2, _3, _4>()
    .test<list<seq_0_1, list<_5>>, _0, _1, _2, _3, _4, _5>()
    .test<list<seq_0_1, list<_5, _6>>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<seq_0_1, list<_5, _6>>, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .test<list<seq_0_1, list<_5, _6>, list<_10>>, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>()
    ;

  test_context<sliding_with_stride_c<0, -1>, smp::sliding_with_stride_c<0, -1>>()
    .test<list<>>()
    .test<list<>, _0>()
    ;

  test_context<sliding_with_stride_c<1, -1>, smp::sliding_with_stride_c<1, -1>>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  ut::not_invocable<smp::sliding_with_stride_c<1, 1, and_<>>, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>();
  ut::not_invocable<smp::sliding_with_stride_c<1, 2, and_<>>, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>();
  ut::not_invocable<smp::sliding_with_stride_c<3, 1, and_<>>, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>();
  ut::not_invocable<smp::sliding_with_stride_c<3, 2, and_<>>, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>();
  ut::not_invocable<smp::sliding_with_stride_c<3, 3, and_<>>, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>();
  ut::not_invocable<smp::sliding_with_stride_c<3, 4, and_<>>, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10,
    _11, _12, _13, _14, _15>();

  ut::not_invocable<smp::sliding_with_stride<_3, _1, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::sliding_with_stride<_1, _2, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::sliding_with_stride<_2, _2, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::sliding_with_stride<_3, _2, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::sliding_with_stride<_5, _2, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::sliding_with_stride<_2, _5, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::sliding_with_stride<smp::always<na>, _1>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::sliding_with_stride<_0, bad_number>, _1, _1, _1, _1>();
  ut::not_invocable<smp::sliding_with_stride<bad_number, _1>, _1, _1, _1, _1>();
  ut::not_invocable<smp::sliding_with_stride<_0, number<-1>, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::sliding_with_stride<_1, number<-1>, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::sliding_with_stride<bad_number, bad_number, bad_function>, _1, _1>();
  ut::not_invocable<smp::sliding_with_stride<smp::always<na>, smp::always<na>>, _1, _1>();
}

TEST_SUITE_END()
