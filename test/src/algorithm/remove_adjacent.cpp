#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/remove_adjacent.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<remove_adjacent_if, equal<>>();
  test_pack2<remove_adjacent_if, void>();

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
    remove_adjacent_if<always<na>>,
    smp::remove_adjacent_if<smp::always<na>>
  >()
    .test<list<>>()
    .not_invocable<list<>, _0>()
    .not_invocable<list<>, _0, _1>()
    .not_invocable<list<>, _0, _1, _2>()
    ;
}

TEST_SUITE_END()
