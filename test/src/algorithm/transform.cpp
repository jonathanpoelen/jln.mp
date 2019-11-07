#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/transform.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<transform, inc<>>()
    .test_binary()
    .test_unary()
    ;

  test_pack<transform, listify>()
    .test_binary()
    .test_unary()
    ;

  ut::same<seq_1_2_3, emp::transform<seq_0_1_2, inc<>>>();

  test_context<transform<inc<>>, smp::transform<smp::inc<>>>()
    .test<list<>>()
    .test<seq_1_2_3, _0, _1, _2>()
    .not_invocable<list<>>()
    ;
}

TEST_SUITE_END()
