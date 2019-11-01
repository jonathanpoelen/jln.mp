#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/at.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace TU::ints;

  IS_SAME(_0, emp::at0<seq_0_1_2_3_4_5_6_7_8_9>);
  IS_SAME(_1, emp::at1<seq_0_1_2_3_4_5_6_7_8_9>);
  IS_SAME(_2, emp::at2<seq_0_1_2_3_4_5_6_7_8_9>);
  IS_SAME(_3, emp::at3<seq_0_1_2_3_4_5_6_7_8_9>);
  IS_SAME(_4, emp::at4<seq_0_1_2_3_4_5_6_7_8_9>);
  IS_SAME(_5, emp::at5<seq_0_1_2_3_4_5_6_7_8_9>);
  IS_SAME(_6, emp::at6<seq_0_1_2_3_4_5_6_7_8_9>);
  IS_SAME(_7, emp::at7<seq_0_1_2_3_4_5_6_7_8_9>);
  IS_SAME(_8, emp::at8<seq_0_1_2_3_4_5_6_7_8_9>);
  IS_SAME(_9, emp::at9<seq_0_1_2_3_4_5_6_7_8_9>);

  IS_SAME(at5<>, at_c<5>);
  IS_SAME(at5<>, at<number<5>>);

  test_context<at<_1>, smp::at<_1>>()
    .test<void, int, void>()
    .test<void, int, void, char>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  test_context<at<_12>, smp::at<_12>>()
    .test<_12, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13>()
    .test<_12, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12>()
    .not_invocable<>()
    .not_invocable<_0>()
    .not_invocable<_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11>()
    ;
}

TEST_SUITE_END()
