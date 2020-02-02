#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/algorithm/sliding.hpp"
// #include "jln/mp/smp/algorithm/sliding.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<list<>, emp::sliding<list<>, _1>>();
  ut::same<list<seq_0>, emp::sliding<seq_0, _1>>();
  ut::same<list<seq_0, seq_1>, emp::sliding<seq_0_1, _1>>();
  ut::same<list<seq_0, seq_1, seq_2>, emp::sliding<seq_0_1_2, _1>>();

  ut::same<list<>, emp::sliding<list<>, _2>>();
  ut::same<list<seq_0>, emp::sliding<seq_0, _2>>();
  ut::same<list<seq_0_1>, emp::sliding<seq_0_1, _2>>();
  ut::same<list<seq_0_1, seq_1_2>, emp::sliding<seq_0_1_2, _2>>();
  ut::same<list<seq_0_1, seq_1_2, seq_2_3>, emp::sliding<seq_0_1_2_3, _2>>();

  ut::same<list<>, emp::sliding<list<>, _3>>();
  ut::same<list<seq_0>, emp::sliding<seq_0, _3>>();
  ut::same<list<seq_0_1>, emp::sliding<seq_0_1, _3>>();
  ut::same<list<seq_0_1_2>, emp::sliding<seq_0_1_2, _3>>();
  ut::same<list<seq_0_1_2, seq_1_2_3>, emp::sliding<seq_0_1_2_3, _3>>();

  ut::same<list<>, emp::sliding<list<>, _1, _2>>();
  ut::same<list<seq_0>, emp::sliding<seq_0, _1, _2>>();
  ut::same<list<seq_0>, emp::sliding<seq_0_1, _1, _2>>();
  ut::same<list<seq_0, seq_2>, emp::sliding<seq_0_1_2, _1, _2>>();
  ut::same<list<seq_0, seq_2>, emp::sliding<seq_0_1_2_3, _1, _2>>();

  ut::same<list<>, emp::sliding<list<>, _2, _2>>();
  ut::same<list<seq_0>, emp::sliding<seq_0, _2, _2>>();
  ut::same<list<seq_0_1>, emp::sliding<seq_0_1, _2, _2>>();
  ut::same<list<seq_0_1, seq_2>, emp::sliding<seq_0_1_2, _2, _2>>();
  ut::same<list<seq_0_1, seq_2_3>, emp::sliding<seq_0_1_2_3, _2, _2>>();

  ut::same<list<>, emp::sliding<list<>, _3, _2>>();
  ut::same<list<seq_0>, emp::sliding<seq_0, _3, _2>>();
  ut::same<list<seq_0_1>, emp::sliding<seq_0_1, _3, _2>>();
  ut::same<list<seq_0_1_2>, emp::sliding<seq_0_1_2, _3, _2>>();
  ut::same<list<seq_0_1_2, seq_2_3>, emp::sliding<seq_0_1_2_3, _3, _2>>();
  ut::same<list<seq_0_1_2, seq_2_3_4>, emp::sliding<list<_0, _1, _2, _3, _4>, _3, _2>>();
  ut::same<list<seq_0_1_2, seq_2_3_4, list<_4, _5, _6>>, emp::sliding<list<_0, _1, _2, _3, _4, _5, _6>, _3, _2>>();

  // test_pack<sliding, listify>()
  //   .test_unary()
  //   .test_binary()
  //   .test_variadic()
  //   ;
  //
  // ut::same<list<_0, _1, _1, _2, _2, _3>, emp::sliding<list<seq_0_1_2, seq_1_2_3>>>();
  //
  // test_context<sliding<>, smp::sliding<>>()
  //   .test<list<>, list<>, list<>>()
  //   .test<list<_0, _1>, list<_0>, list<_1>>()
  //   .test<list<_0, _1>, list<>, list<_0, _1>>()
  //   .test<list<_0, _1>, list<_0, _1>, list<>>()
  //   .test<list<bad_number>, list<>, list<bad_number>>()
  //   .not_invocable<list<>, int>()
  //   .not_invocable<list<bad_number>, list<bad_number>>()
  //   ;
}

TEST_SUITE_END()
