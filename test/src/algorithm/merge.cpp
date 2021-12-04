#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/merge.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<merge, listify>();
  test_pack2<merge, void>();

  ut::same<list<_0, _1, _1, _2, _2, _3>, emp::merge<list<seq_0_1_2, seq_1_2_3>>>();

  test_context<merge<>, smp::merge<>>()
    .test<list<>, list<>, list<>>()
    .test<list<_0, _1>, list<_0>, list<_1>>()
    .test<list<_0, _1>, list<>, list<_0, _1>>()
    .test<list<_0, _1>, list<_0, _1>, list<>>()
    .test<list<bad_number>, list<>, list<bad_number>>()
    .not_invocable<list<>, int>()
    .not_invocable<list<bad_number>, list<bad_number>>()
    ;

  ut::not_invocable<smp::merge<smp::always<na>>, _1, _1>();
  ut::not_invocable<smp::merge<bad_function>, _1, _1>();
  ut::not_invocable<smp::merge<always<void>>, _1, _1>();
  ut::not_invocable<smp::merge<bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::merge<always<true_>, bad_function>, _1, _1>();
}

TEST_SUITE_END()
