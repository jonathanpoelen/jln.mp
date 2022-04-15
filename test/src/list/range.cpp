#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/range.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<range, _1, _2>();

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
  ut::same<list<>,
    emp::range_c<seq_0_1_2_3_4_5_6_7_8_9, 0, -20>>();
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

  test_context<range<_2, _4>, smp::range<_2, _4>>()
    .test<list<_2, _3>, _0, _1, _2, _3, _4, _5>()
    ;

  ut::not_invocable<smp::range<smp::always<na>, _2>, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<_0, _9, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<_2, _9, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<_0, number<-1>, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<_1, number<-1>, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<_1, number<-2>, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<number<-1>, number<-1>, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<number<-3>, _10, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<number<3>, number<-3>, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<number<-9>, number<-7>, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<number<-10>, number<-2>, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<number<-11>, number<-2>, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<number<-22>, _0, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<bad_number, bad_number, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<_1, bad_number>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<bad_number, _2>, _1, _1, _1, _1, _1, _1>();
}

TEST_SUITE_END()
