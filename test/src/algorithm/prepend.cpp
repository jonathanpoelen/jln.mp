#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/prepend.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<prepend, list<>>()
    .test_binary()
    .test_unary()
    ;

  ut::same<list<_3, _4, _0, _1, _2>, emp::prepend<seq_0_1_2, _3, _4>>();

  test_context<prepend<list<_9>>, smp::prepend<list<_9>>>()
    .test<list<_9>>()
    .test<list<_0, _1, _2, _9>, _0, _1, _2>()
    ;
}

TEST_SUITE_END()
