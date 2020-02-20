#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/all_of.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<false_, emp::all_of<seq_0_1_2, identity>>();
  ut::same<true_, emp::all_of<seq_1_2_3, identity>>();

  test_pack2<all_of, identity>();
  test_pack2<all_of>();

  test_context<all_of<identity>, smp::all_of<smp::identity>>()
    .test<true_>()
    .test<false_, _0, _0>()
    .test<false_, _0, _0, _1>()
    .test<true_, _3, _1>()
    ;

  test_context<all_of<less_than_c<3>>, smp::all_of<smp::less_than_c<3>>>()
    .test<true_, _1, _0>()
    .test<false_, _1, _0, _3>()
    .not_invocable<list<>>()
    ;
}

TEST_SUITE_END()
