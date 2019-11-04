#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/any_of.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace TU::ints;

  IS_SAME(false_, emp::any_of<seq_0_0_0, identity>);
  IS_SAME(true_, emp::any_of<seq_0_1_2, identity>);
  IS_SAME(true_, emp::any_of<seq_1_2_3, identity>);

  test_pack<any_of, identity>()
    .test_binary()
    .test_unary()
  ;

  test_context<any_of<identity>, smp::any_of<smp::identity>>()
    .test<false_>()
    .test<false_, _0, _0>()
    .test<true_, _0, _0, _1>()
    .test<true_, _3, _1>()
    ;

  test_context<any_of<less_than_c<3>>, smp::any_of<smp::less_than_c<3>>>()
    .test<true_, _1, _0>()
    .test<true_, _1, _0, _3>()
    .test<false_, _3, _3>()
    .not_invocable<list<>>()
    ;
}

TEST_SUITE_END()
