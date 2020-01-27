#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/append.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<append, list<>>()
    .test_binary()
    .test_unary()
    ;

  ut::same<list<_0, _1, _2, _3, _4>, emp::append<seq_0_1_2, _3, _4>>();

  test_context<append<list<_9>>, smp::append<list<_9>>>()
    .test<list<_9>>()
    .test<list<_9, _0, _1, _2>, _0, _1, _2>()
    ;
}

TEST_SUITE_END()
