#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/remove_adjacent.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<remove_adjacent, inc<>>()
    .test_binary()
    .test_unary()
    ;

  test_pack<remove_adjacent, listify>()
    .test_binary()
    .test_unary()
    ;

  ut::same<seq_1_2_3, emp::remove_adjacent<seq_0_1_2, inc<>>>();

  test_context<remove_adjacent<inc<>>, smp::remove_adjacent<smp::inc<>>>()
    .test<list<>>()
    .test<seq_1_2_3, _0, _1, _2>()
    .not_invocable<list<>>()
    ;
}

TEST_SUITE_END()
