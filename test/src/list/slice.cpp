#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/slice.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<slice, _1, _2, _1>();
  test_pack3<slice, void, void, void>();

  ut::same<emp::numbers<3, 4, 5, 6>, emp::slice_c<
    seq_0_1_2_3_4_5_6_7_8_9, 3, 4>>();
  ut::same<emp::numbers<0, 2, 4>, emp::slice_c<
    seq_0_1_2_3_4_5_6_7_8_9, 0, 3, 2>>();

  test_context<slice_c<2, 3>, smp::slice_c<2, 3>>()
    .test<list<_2, _3, _4>, _0, _1, _2, _3, _4, _5>()
    .test<list<_2, _3, _4>, _0, _1, _2, _3, _4>()
    .not_invocable<_0, _2, _3>()
    .not_invocable<_0, _2>()
    .not_invocable<_0>()
    .not_invocable<>()
    ;

  test_context<slice_c<2, 3, 2>, smp::slice_c<2, 3, 2>>()
    .test<list<_2, _4, _6>, _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<list<_2, _4, _6>, _0, _1, _2, _3, _4, _5, _6>()
    .not_invocable<_0, _1, _2, _3, _4, _5>()
    .not_invocable<_0, _2, _3>()
    .not_invocable<_0, _2>()
    .not_invocable<_0>()
    .not_invocable<>()
    ;

  test_context<slice_c<0, 2, 5>, smp::slice_c<0, 2, 5>>()
    .test<list<_0, _5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_0, _5>, _0, _1, _2, _3, _4, _5, _6>()
    .not_invocable<_0, _1, _2, _3, _4>()
    ;

  ut::not_invocable<smp::slice_c<2, 3, 0>, _0, _1, _2, _3, _4, _5>();

  ut::not_invocable<smp::slice<_2, _3, _2, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::slice<bad_number, _3, _2, bad_function>, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::slice<_2, bad_number, _2, bad_function>, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::slice<_2, _3, bad_number, bad_function>, _1, _1, _1, _1, _1, _1, _1>();
}

TEST_SUITE_END()

