#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/all_of.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/number/to_bool.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<false_, emp::all_of<seq_0_1_2, to_bool<>>>();
  ut::same<true_, emp::all_of<seq_1_2_3, to_bool<>>>();

  test_pack2<all_of, to_bool<>>();
  test_pack2<all_of>();

  test_context<all_of<to_bool<>>, smp::all_of<smp::to_bool<>>>()
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

  ut::not_invocable<smp::all_of<smp::always<na>>, _1>();
  ut::not_invocable<smp::all_of<bad_function>, _1>();
  ut::not_invocable<smp::all_of<always<void>>, _1>();
  ut::not_invocable<smp::all_of<always<true_>, bad_function>>();
  ut::not_invocable<smp::all_of<always<true_>, bad_function>, _1>();
  ut::not_invocable<smp::all_of<bad_function, bad_function>>();
  ut::not_invocable<smp::all_of<bad_function, bad_function>, _1>();
}

TEST_SUITE_END()
