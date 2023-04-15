#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/remove_adjacent.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_binary_pack<remove_adjacent_if>();
  test_mulary_pack<remove_adjacent_if, listify>();

  ut::same<emp::numbers<0, 1, 2, 3, 4>, emp::remove_adjacent_if<
    emp::numbers<0, 0, 1, 2, 3, 4, 4>, equal<>>>();

  test_context<
    remove_adjacent_if<equal<>>,
    smp::remove_adjacent_if<smp::equal<>>
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
    remove_adjacent_if<not_equal<>>,
    smp::remove_adjacent_if<smp::not_equal<>>
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
    remove_adjacent_if<always<na>>,
    smp::remove_adjacent_if<smp::always<na>>
  >()
    .test<list<>>()
    .not_invocable<list<>, _0>()
    .not_invocable<list<>, _0, _1>()
    .not_invocable<list<>, _0, _1, _2>()
    ;

  ut::not_invocable<smp::remove_adjacent<bad_function>>();
  ut::not_invocable<smp::remove_adjacent<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::remove_adjacent<bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::remove_adjacent_if<bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::remove_adjacent_if<always<void>>, _1, _1, _1>();
  ut::not_invocable<smp::remove_adjacent_if<bad_function, bad_function>>();
  ut::not_invocable<smp::remove_adjacent_if<always<true_>, bad_function>>();
  ut::not_invocable<smp::remove_adjacent_if<bad_function, bad_function>, _1, _1, _1, _1>();
}

TEST_SUITE_END()
