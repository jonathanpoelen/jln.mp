#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/index.hpp"
#include "jln/mp/smp/algorithm/starts_with.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<index_of, int>();
  test_pack2<index_if_xs, is<int>>();

  ut::same<_2, emp::index_of<seq_0_1_2_3, _2>>();
  ut::same<_4, emp::index_of<seq_0_1_2_3, int>>();

  test_context<index_if<equal_to<_3>>, smp::index_if<smp::equal_to<_3>>>()
    .test<_0>()
    .test<_3, _0, _1, _2, _3>()
    .test<_2, _1, _2, _3, _4>()
    .test<_2, _1, _2, _3>()
    .test<_0, _3, _4>()
    .test<_0, _3>()
    .not_invocable<void, void>()
    .not_invocable<void>()
    ;

  test_context<
    index_if_xs<size<is<_2>>>,
    smp::index_if_xs<smp::size<smp::is<_2>>>
  >()
    .test<_0>()
    .test<_1, _0>()
    .test<_0, _1, _2>()
    .test<_1, _1, _2, _3>()
    .test<_2, _1, _2, _3, _4>()
    ;

  test_context<
    index_if_xs<starts_with<list<>>, identity, always<void>>,
    smp::index_if_xs<smp::starts_with<list<>>, smp::identity, smp::always<void>>
  >()
    .test<void>()
    .test<_0, _0>()
    ;

  test_context<
    index_if_xs<starts_with<list<_1>>, identity, always<void>>,
    smp::index_if_xs<smp::starts_with<list<_1>>, smp::identity, smp::always<void>>
  >()
    .test<void>()
    .test<void, _2>()
    .test<_0, _1>()
    .test<_0, _1, _2>()
    .test<_1, _0, _1>()
    .test<_1, _0, _1, _2>()
    ;

  test_context<
    index_if_xs<starts_with<list<_1, _2>>, identity, always<void>>,
    smp::index_if_xs<smp::starts_with<list<_1, _2>>, smp::identity, smp::always<void>>
  >()
    .test<void>()
    .test<void, _2>()
    .test<_0, _1, _2>()
    .test<_0, _1, _2, _3>()
    .test<_1, _0, _1, _2>()
    .test<_1, _0, _1, _2, _3>()
    .test<void, _1, _0, _2, _3>()
    ;

  ut::not_invocable<smp::index_of<void, bad_function, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::index_if<smp::always<_3>>, _1, _1, _1>();
  ut::not_invocable<smp::index_if<smp::always<na>>, _1, _1, _1, _1>();
  ut::not_invocable<smp::index_if<void>, _1, _1, _1, _1>();
  ut::not_invocable<smp::index_if<always<void>>, _1, _1, _1, _1>();
  ut::not_invocable<smp::index_if<always<_1>, bad_function, size<>>, _1, _1, _1, _1>();
  ut::not_invocable<smp::index_if<always<_0>, identity, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::index_if<bad_function>, _1, _1, _1, _1>();
}

TEST_SUITE_END()
