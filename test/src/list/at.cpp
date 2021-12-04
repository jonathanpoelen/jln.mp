#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/at.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<_0, emp::at0<seq_0_1_2_3_4_5_6_7_8_9>>();
  ut::same<_1, emp::at1<seq_0_1_2_3_4_5_6_7_8_9>>();
  ut::same<_2, emp::at2<seq_0_1_2_3_4_5_6_7_8_9>>();
  ut::same<_3, emp::at3<seq_0_1_2_3_4_5_6_7_8_9>>();
  ut::same<_4, emp::at4<seq_0_1_2_3_4_5_6_7_8_9>>();
  ut::same<_5, emp::at5<seq_0_1_2_3_4_5_6_7_8_9>>();
  ut::same<_6, emp::at6<seq_0_1_2_3_4_5_6_7_8_9>>();
  ut::same<_7, emp::at7<seq_0_1_2_3_4_5_6_7_8_9>>();
  ut::same<_8, emp::at8<seq_0_1_2_3_4_5_6_7_8_9>>();
  ut::same<_9, emp::at9<seq_0_1_2_3_4_5_6_7_8_9>>();

  ut::same<at5<>, at_c<5>>();
  ut::same<at5<>, at<number<5>>>();

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

  ut::not_invocable<smp::at<smp::always<na>>>();
  ut::not_invocable<smp::at<_1, bad_function>>();
  ut::not_invocable<smp::at<_1, bad_function>, _1, _1>();
}

TEST_SUITE_END()
