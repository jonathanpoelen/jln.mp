#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/adjacent_difference.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<adjacent_difference>();

  ut::same<emp::numbers<0, 0, 1, 2, 4, -3, 1, 0>, emp::adjacent_difference<
    emp::numbers<0, 0, 1, 3, 7, 4, 5, 5>>>();

  test_context<adjacent_difference<>, smp::adjacent_difference<>>()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<seq_0_0, _0, _0>()
    .test<seq_0_0_0, _0, _0, _0>()
    .test<list<_1, _2, number<-2>, _1>, _1, _3, _1, _2>()
    .not_invocable<void, _0, _1, _2>()
    .not_invocable<_0, _1, _2, void>()
    ;

  ut::not_invocable<smp::adjacent_difference<bad_function>, _1>();
}

TEST_SUITE_END()
