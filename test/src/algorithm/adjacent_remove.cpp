#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/adjacent_remove.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_binary_pack<adjacent_remove_if>();
  test_mulary_pack<adjacent_remove_if, listify>();

  ut::same<emp::numbers<0, 1, 2, 3, 4>, emp::adjacent_remove_if<
    emp::numbers<0, 0, 1, 2, 3, 4, 4>, equal<>>>();

  test_context<
    adjacent_remove_if<equal<>>,
    smp::adjacent_remove_if<smp::equal<>>
  >()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<seq_0, _0, _0>()
    .test<seq_0_1, _0, _1>()
    .test<seq_0_1_2, _0, _1, _2>()
    .test<seq_0_1_2, _0, _0, _1, _2>()
    .test<seq_0_1_2, _0, _1, _2, _2>()
    .test<seq_0_1_2, _0, _1, _1, _2>()
    .test<seq_0_1_2, _0, _0, _1, _1, _2, _2>()
    .test<emp::numbers<0, 1, 2, 0>, _0, _1, _2, _0>()
    ;

  test_context<
    adjacent_remove_if<not_equal<>>,
    smp::adjacent_remove_if<smp::not_equal<>>
  >()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<seq_0_0, _0, _0>()
    .test<seq_0, _0, _1>()
    .test<seq_0, _0, _1, _2>()
    .test<seq_0_0, _0, _0, _1, _2>()
    .test<seq_0_2, _0, _1, _2, _2>()
    .test<seq_0_1, _0, _1, _1, _2>()
    .test<emp::numbers<0, 0, 1, 2>, _0, _0, _1, _1, _2, _2>()
    .test<seq_0, _0, _1, _2, _0>()
    ;

  test_context<
    adjacent_remove_if<always<na>>,
    smp::adjacent_remove_if<smp::always<na>>
  >()
    .test<list<>>()
    .not_invocable<list<>, _0>()
    .not_invocable<list<>, _0, _1>()
    .not_invocable<list<>, _0, _1, _2>()
    ;

  ut::not_invocable<smp::adjacent_remove<bad_function>>();
  ut::not_invocable<smp::adjacent_remove<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::adjacent_remove<bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::adjacent_remove_if<bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::adjacent_remove_if<always<void>>, _1, _1, _1>();
  ut::not_invocable<smp::adjacent_remove_if<bad_function, bad_function>>();
  ut::not_invocable<smp::adjacent_remove_if<always<true_>, bad_function>>();
  ut::not_invocable<smp::adjacent_remove_if<bad_function, bad_function>, _1, _1, _1, _1>();
}

TEST_SUITE_END()
