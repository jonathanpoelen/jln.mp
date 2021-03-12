#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/after.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using l0 = list<>;
  using l1 = list<_1>;
  using l2 = list<_1, _2>;

  test_pack2<after, l0>();
  test_pack2<after, l1>();
  test_pack2<after, l2>();
  test_pack3<after>();

  test_context<
    after<l0, listify, always<void>>,
    smp::after<l0, smp::listify, smp::always<void>>
  >()
    .test<list<>>()
    .test<seq_0, _0>()
    ;

  test_context<
    after<l1, listify, always<void>>,
    smp::after<l1, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<list<>, _1>()
    .test<list<>, _0, _1>()
    .test<seq_2, _1, _2>()
    .test<seq_2, _0, _1, _2>()
    .test<seq_2_3, _0, _1, _2, _3>()
    ;

  test_context<
    after<l2, listify, always<void>>,
    smp::after<l2, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<void, _0, _1>()
    .test<list<>, _0, _1, _2>()
    .test<seq_3, _0, _1, _2, _3>()
    .test<seq_3_2, _0, _1, _2, _3, _2>()
    ;

  test_context<
    after<l1, listify, size<>>,
    smp::after<l1, smp::listify, smp::size<>>
  >()
    .test<_1, _0>()
    ;

  test_context<after<int>, smp::after<int>>()
    .not_invocable<>()
    .not_invocable<int>()
    ;

  ut::not_invocable<smp::after<int>>();
  ut::not_invocable<smp::after<l0, bad_function>>();
}

TEST_SUITE_END()
