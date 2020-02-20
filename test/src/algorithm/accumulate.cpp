#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/accumulate.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<accumulate, listify>();
  test_pack2<accumulate>();

  ut::same<list<list<list<list<list<_9, _0>, _1>, _4>, _3>, _2>,
    emp::accumulate<list<seq_0_1, seq_4_3_2>, _9, listify>>();

  test_context<accumulate<add<>>, smp::accumulate<smp::add<>>>()
    .test<_0, _0>()
    .test<list<>, list<>>()
    .test<_9, _0, seq_1_2, seq_1_2_3>()
    .test<_9, _0, list<>, seq_1_2, list<>, seq_1_2_3>()
    .not_invocable<>()
    .not_invocable<_0, list<list<>>>()
    ;
}

TEST_SUITE_END()
