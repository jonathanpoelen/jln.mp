#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/remove.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<remove_if, same_as<int>>();
  test_pack2<remove_if, void>();

  ut::same<emp::numbers<1, 2>, emp::remove_if<seq_0_1_2, same_as<_0>>>();
  ut::same<emp::numbers<0, 2>, emp::remove<seq_0_1_2, _1>>();

  test_context<
    remove_if<same_as<_1>>,
    smp::remove_if<same_as<_1>>,
    0
  >()
    .test<list<>>()
    .test<seq_0_0_0, _0, _0, _0>()
    .test<list<>, _1, _1, _1>()
    .test<emp::numbers<0, 3>, _0, _1, _3>()
    ;

  test_context<
    remove_if<always<na>>,
    smp::remove_if<always<na>>,
    0
  >()
    .test<list<>>()
    .not_invocable<_0, _0, _0>()
    .not_invocable<_0, _1, _3>()
    ;

  test_context<remove<_1>, smp::remove<_1>, 0>()
    .test<list<>>()
    .test<seq_0_0_0, _0, _0, _0>()
    .test<list<>, _1, _1, _1>()
    .test<emp::numbers<0, 3>, _0, _1, _3>()
    ;
}

TEST_SUITE_END()
