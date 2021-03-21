#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/is_disjoint.hpp"
#include "jln/mp/smp/functional/each.hpp"
#include "jln/mp/smp/list/at.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack3<is_disjoint>();

  ut::same<_1, emp::is_disjoint<emp::numbers<0, 1, 2>, emp::numbers<3, 4, 5>>>();
  ut::same<_0, emp::is_disjoint<emp::numbers<0, 1, 2>, emp::numbers<3, 2>>>();

  test_context<is_disjoint<>, smp::is_disjoint<>>()
    .test<_1>()
    .test<_1, list<>>()
    .test<_1, list<>, list<>>()
    .test<_1, list<>, list<>, list<>>()
    .test<_1, list<>, list<>, list<>, list<>>()
    .test<_1, seq_0_1_2_3, list<_5>, list<_5>, list<_4, _8>>()
    .test<_0, seq_0, seq_0>()
    .test<_0, seq_0, seq_1, seq_0>()
    .test<_0, seq_0_1_2_3, seq_2>()
    .test<_0, seq_0_1_2_3, list<_4, _2>>()
    .test<_0, seq_0_1_2_3, list<_5>, list<_5>, list<_4, _2>>()
    .not_invocable<_0>()
    .not_invocable<list<>, _0>()
    ;

  test_context<is_disjoint_with<equal<>>, smp::is_disjoint_with<smp::equal<>>>()
    .test<_1>()
    .test<_1, list<>>()
    .test<_1, list<>, list<>>()
    .test<_1, list<>, list<>, list<>>()
    .test<_1, list<>, list<>, list<>, list<>>()
    .test<_1, seq_0_1_2_3, list<_5>, list<_5>, list<_4, _8>>()
    .test<_0, seq_0, seq_0>()
    .test<_0, seq_0, seq_1, seq_0>()
    .test<_0, seq_0_1_2_3, seq_2>()
    .test<_0, seq_0_1_2_3, list<_4, _2>>()
    .test<_0, seq_0_1_2_3, list<_5>, list<_5>, list<_4, _2>>()
    .not_invocable<_0>()
    .not_invocable<list<>, _0>()
    ;

  ut::not_invocable<smp::is_disjoint<bad_function>>();
  ut::not_invocable<smp::is_disjoint_with<always<void>>, list<_1>, list<_0>>();
  ut::not_invocable<smp::is_disjoint_with<always<void>, bad_function>>();
  ut::not_invocable<smp::is_disjoint_with<always<true_>, bad_function>>();
  ut::not_invocable<smp::is_disjoint_with<bad_function, bad_function>>();
  ut::not_invocable<smp::is_disjoint_with<bad_function, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
