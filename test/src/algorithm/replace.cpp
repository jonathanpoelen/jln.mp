#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/replace.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<replace_if, same_as<int>, void>();
  test_pack2<replace_if, void, void>();

  ut::same<emp::numbers<1, 1, 2>, emp::replace_if<seq_0_1_2, same_as<_0>, _1>>();
  ut::same<emp::numbers<1, 1, 2>, emp::replace<seq_0_1_2, _0, _1>>();

  test_context<
    replace_if<same_as<_1>, _2>,
    smp::replace_if<same_as<_1>, _2>,
    0
  >()
    .test<list<>>()
    .test<seq_0_0_0, _0, _0, _0>()
    .test<seq_2_2_2, _1, _1, _1>()
    .test<emp::numbers<0, 2, 3>, _0, _1, _3>()
    ;

  test_context<
    replace_if<same_as<_1>, na>,
    smp::replace_if<same_as<_1>, na>,
    0
  >()
    .test<list<>>()
    .test<seq_0_0_0, _0, _0, _0>()
    .not_invocable<_0, _1, _3>()
    ;

  test_context<
    replace_if<always<na>, _0>,
    smp::replace_if<always<na>, _0>,
    0
  >()
    .test<list<>>()
    .not_invocable<_0, _0, _0>()
    .not_invocable<_0, _1, _3>()
    ;

  test_context<replace<_1, _2>, smp::replace<_1, _2>, 0>()
    .test<list<>>()
    .test<seq_0_0_0, _0, _0, _0>()
    .test<seq_2_2_2, _1, _1, _1>()
    .test<emp::numbers<0, 2, 3>, _0, _1, _3>()
    ;

  test_context<replace<_1, na>, smp::replace<_1, na>, 0>()
    .test<list<>>()
    .test<seq_0_0_0, _0, _0, _0>()
    .not_invocable<_0, _1, _3>()
    ;
}

TEST_SUITE_END()
