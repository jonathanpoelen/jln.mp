#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/any_of.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<false_, emp::any_of<seq_0_0_0, identity>>();
  ut::same<true_, emp::any_of<seq_0_1_2, identity>>();
  ut::same<true_, emp::any_of<seq_1_2_3, identity>>();

  test_pack2<any_of, identity>();
  test_pack2<any_of>();

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

  ut::not_invocable<smp::any_of<bad_function>, _1>();
  ut::not_invocable<smp::any_of<always<void>>, _1>();
  ut::not_invocable<smp::any_of<always<true_>, bad_function>>();
  ut::not_invocable<smp::any_of<always<true_>, bad_function>, _1>();
  ut::not_invocable<smp::any_of<bad_function, bad_function>>();
  ut::not_invocable<smp::any_of<bad_function, bad_function>, _1>();
}

TEST_SUITE_END()
