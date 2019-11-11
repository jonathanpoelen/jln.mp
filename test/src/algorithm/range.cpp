#include "test.hpp"
#include "test/numbers.hpp"

// TODO smp
#include "jln/mp/algorithm/range.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  // test_pack<transform, inc<>>()
  //   .test_binary()
  //   .test_unary()
  //   ;
  //
  // test_pack<transform, listify>()
  //   .test_binary()
  //   .test_unary()
  //   ;

  ut::same<seq_0_1_2_3_4_5_6_7_8_9,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, 0, 10>>();
  ut::same<seq_0_1_2_3_4_5_6_7_8_9,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, 0, -1>>();
  ut::same<list<>,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, -1, -1>>();
  ut::same<list<>,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, -1, 10>>();
  ut::same<seq_1_2_3,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, 1, 4>>();

  ut::same<emp::numbers<7, 8, 9>,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, -3, 10>>();
  ut::same<emp::numbers<3, 4, 5, 6, 7>,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, 3, -3>>();
  ut::same<emp::numbers<1, 2, 3>,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, -9, -7>>();
  ut::same<emp::numbers<0, 1, 2, 3, 4, 5, 6, 7, 8>,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, -10, -2>>();
  ut::same<emp::numbers<0, 1, 2, 3, 4, 5, 6, 7, 8>,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, -11, -2>>();

  ut::same<list<>,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, 12, 111>>();
  ut::same<list<>,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, 12, -1>>();
  ut::same<list<>,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, 12, -2>>();
  // ut::same<list<>,
  //   emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, 0, -20>>();
  ut::same<list<>,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, -22, -20>>();
  ut::same<list<>,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, -22, 0>>();

  ut::same<seq_0_1,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, -22, 2>>();
  ut::same<seq_0_1_2_3_4_5_6_7_8_9,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, -22, -1>>();

  ut::same<emp::numbers<1, 2, 3, 4, 5, 6, 7, 8, 9>,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, 1, -1>>();
  ut::same<emp::numbers<1, 2, 3, 4, 5, 6, 7, 8>,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, 1, -2>>();

  // TODO smp
  // test_context<transform<inc<>>, void>()
  //   .test<list<>>()
  //   .test<seq_1_2_3, _0, _1, _2>()
  //   .not_invocable<list<>>()
  //   ;
}

TEST_SUITE_END()
