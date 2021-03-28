#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/none_of.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<true_, emp::none_of<seq_0_0_0, identity>>();
  ut::same<false_, emp::none_of<seq_0_1_2, identity>>();
  ut::same<false_, emp::none_of<seq_1_2_3, identity>>();

  test_pack2<none_of, void>();
  test_pack2<none_of, identity>();

  test_context<none_of<identity>, smp::none_of<smp::identity>, 0>()
    .test<true_>()
    .test<true_, _0, _0>()
    .test<false_, _0, _0, _1>()
    .test<false_, _3, _1>()
    ;

  test_context<none_of<less_than_c<3>>, smp::none_of<smp::less_than_c<3>>, 0>()
    .test<false_, _1, _0>()
    .test<false_, _1, _0, _3>()
    .test<true_, _3, _3>()
    .not_invocable<list<>>()
    ;

  ut::not_invocable<smp::none_of<bad_function>, _1>();
  ut::not_invocable<smp::none_of<always<void>>, _1>();
  ut::not_invocable<smp::none_of<always<true_>, bad_function>>();
  ut::not_invocable<smp::none_of<always<true_>, bad_function>, _1>();
  ut::not_invocable<smp::none_of<bad_function, bad_function>>();
  ut::not_invocable<smp::none_of<bad_function, bad_function>, _1>();
}

TEST_SUITE_END()
