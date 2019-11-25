#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/slice.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<slice, _1, _2, _1>()
    .test_variadic()
    .test_binary()
    .test_unary()
    ;

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

  ut::not_invocable<smp::slice_c<2, 3, 0>,
    _0, _1, _2, _3, _4, _5>();
}

TEST_SUITE_END()

