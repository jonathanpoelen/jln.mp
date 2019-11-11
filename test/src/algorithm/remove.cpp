#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/remove.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<remove, int>()
    .test_binary()
    .test_unary()
    ;

  ut::same<emp::numbers<0, 2>, emp::remove<seq_0_1_2, _1>>();

  test_context<remove<_1>, smp::remove<_1>, 0>()
    .test<list<>>()
    .test<seq_0_0_0, _0, _0, _0>()
    .test<list<>, _1, _1, _1>()
    .test<emp::numbers<0, 3>, _0, _1, _3>()
    ;
}

TEST_SUITE_END()
