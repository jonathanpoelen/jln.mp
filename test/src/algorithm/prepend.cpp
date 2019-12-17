#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/prepend.hpp"

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

  test_context<prepend<inc<>>, smp::prepend<smp::inc<>>>()
    .test<list<>>()
    .test<seq_1_2_3, _0, _1, _2>()
    .not_invocable<list<>>()
    ;
}

TEST_SUITE_END()
