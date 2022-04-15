#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/accumulate.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_binary_pack<accumulate>();
  test_mulary_pack<accumulate, listify>();

  ut::same<list<list<list<_9, _0, _3>, _1, _4>, _2, _5>,
    emp::accumulate<list<seq_0_1_2, emp::numbers<3, 4, 5>>, _9, listify>>();

  test_context<accumulate<add<>>, smp::accumulate<smp::add<>>>()
    .test<_0, _0>()
    .test<list<>, list<>>()
    .test<_15, _0, seq_2_3_4, seq_1_2_3>()
    .not_invocable<>()
    .not_invocable<_0, list<list<>>>()
    .not_invocable<_0, seq_0, seq_0_0>()
    ;

  ut::not_invocable<smp::accumulate<smp::always<na>>>();
  ut::not_invocable<smp::accumulate<bad_function>>();
  ut::not_invocable<smp::accumulate<bad_function>, _1, _1>();
  ut::not_invocable<smp::accumulate<bad_function, bad_function>>();
  ut::not_invocable<smp::accumulate<smp::add<>, bad_function>>();
  ut::not_invocable<smp::accumulate<bad_function, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
