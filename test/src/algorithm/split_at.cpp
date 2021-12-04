#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/split_at.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/list/push_back.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<list<seq_0_1_2_3, list<_4, _5, _6, _7, _8, _9>>,
    emp::split_at<seq_0_1_2_3_4_5_6_7_8_9, _4>>();

  test_pack3<split_at, _3>();
  test_pack3<split_at>();

  test_context<split_at<_3>, smp::split_at<_3>, 0>()
    .test<list<seq_1_2_3, list<>>, _1, _2, _3>()
    .test<list<seq_1_2_3, list<_4>>, _1, _2, _3, _4>()
    .not_invocable<>()
    .not_invocable<_1>()
    .not_invocable<_1, _2>()
    ;

  test_context<split_at<_0>, smp::split_at<_0>, 0>()
    .test<list<list<>, list<>>>()
    .test<list<list<>, seq_1>, _1>()
    .test<list<list<>, seq_1_2_3>, _1, _2, _3>()
    ;

  ut::not_invocable<smp::split_at_c<-1>, _1, _1, _1>();
  ut::not_invocable<smp::split_at<_1, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::split_at<bad_number>, _1, _1, _1>();
  ut::not_invocable<smp::split_at<bad_number, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()

