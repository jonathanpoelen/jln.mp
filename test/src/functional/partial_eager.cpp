#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/functional/partial_eager.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

struct foo
{
  template<class, class>
  using f = int;
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using yes = always<true_>;
  using no = always<false_>;

  test_pack2<partial_eager>();
  test_pack2<partial_eager, yes, yes>();
  test_pack2<partial_eager, yes, no>();
  test_pack2<partial_eager, yes>();

  ut::same<list<list<void>, list<void, void, void>>, partial_eager<listify, listify, listify>
    ::template f<void, void, void, void>>();

  ut::same<int, partial_eager<identity, identity, foo>::template f<void, void>>();

  test_context<partial_eager<listify>, smp::partial_eager<smp::listify>>()
    .test<list<>>()
    .test<seq_0, _0>()
    ;

  test_context<
    partial_eager<listify, listify, listify>,
    smp::partial_eager<smp::listify, smp::listify, smp::listify>
  >()
    .test<list<seq_0, list<>>, _0>()
    .test<list<seq_0, seq_0>, _0, _0>()
    .test<list<seq_0, seq_0_0>, _0, _0, _0>()
    ;

  test_context<
    partial_eager<inc<>, dec<>, listify>,
    smp::partial_eager<smp::inc<>, smp::dec<>, smp::listify>
  >()
    .test<list<_1, _3>, _0, _4>()
    .not_invocable<list<_1, _3, _2>, _0, _4, _2>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  test_context<
    partial_eager<inc<>, inc<>, inc<>, inc<>, listify>,
    smp::partial_eager<smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::listify>
  >()
    .test<list<_2, _2, _2, _2>, _1, _1, _1, _1>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    .not_invocable<_0, _0, _0>()
    .not_invocable<_1, _1, _1, _1, _1>()
    ;

  ut::not_invocable<smp::partial_eager<bad_function>>();
  ut::not_invocable<smp::partial_eager<bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_eager<identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_eager<bad_function, bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_eager<identity, identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::lift<smp::partial_eager>>();
}

TEST_SUITE_END()
