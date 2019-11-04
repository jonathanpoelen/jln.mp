#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/none_of.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace TU::ints;

  IS_SAME(true_, emp::none_of<seq_0_0_0, identity>);
  IS_SAME(false_, emp::none_of<seq_0_1_2, identity>);
  IS_SAME(false_, emp::none_of<seq_1_2_3, identity>);

  test_pack<none_of, identity>()
    .test_binary()
    .test_unary()
  ;

  test_context<none_of<identity>, smp::none_of<smp::identity>>()
    .test<true_>()
    .test<true_, _0, _0>()
    .test<false_, _0, _0, _1>()
    .test<false_, _3, _1>()
    ;

  test_context<none_of<less_than_c<3>>, smp::none_of<smp::less_than_c<3>>>()
    .test<false_, _1, _0>()
    .test<false_, _1, _0, _3>()
    .test<true_, _3, _3>()
    .not_invocable<list<>>()
    ;
}

TEST_SUITE_END()
