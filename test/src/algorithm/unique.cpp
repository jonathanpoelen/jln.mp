#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/unique.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<unique>()
    .test_variadic()
    .test_binary()
    .test_unary()
    ;

  ut::same<seq_0_1_2, emp::unique<emp::numbers<0, 1, 0, 2, 2>>>();

  test_context<unique<>, smp::unique<>>()
    .test<list<>>()
    .test<seq_0_1_2, _0, _1, _2>()
    .test<seq_0, _0, _0, _0, _0, _0>()
    .test<seq_0_1_2_3, _0, _0, _1, _0, _2, _2, _2, _0, _0, _3>()
    ;
}

TEST_SUITE_END()
