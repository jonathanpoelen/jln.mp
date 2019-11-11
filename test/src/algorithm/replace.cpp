#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/replace.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<replace, int, void>()
    .test_binary()
    .test_unary()
    ;

  ut::same<emp::numbers<1, 1, 2>, emp::replace<seq_0_1_2, _0, _1>>();

  test_context<replace<_1, _2>, smp::replace<_1, _2>, 0>()
    .test<list<>>()
    .test<seq_0_0_0, _0, _0, _0>()
    .test<seq_2_2_2, _1, _1, _1>()
    .test<emp::numbers<0, 2, 3>, _0, _1, _3>()
    ;

  test_context<replace<_1, na>, smp::replace<_1, na>, 0>()
    .test<list<>>()
    .test<seq_0_0_0, _0, _0, _0>()
    .not_invocable<_0, _1, _3>()
    ;
}

TEST_SUITE_END()
