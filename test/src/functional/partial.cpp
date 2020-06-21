#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/functional/partial.hpp"
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

  test_pack2<partial>();
  test_pack2<partial, yes, yes>();
  test_pack2<partial, yes, no>();
  test_pack2<partial, yes>();

  ut::same<list<list<void>, list<void>, void, void>, partial<listify, listify, listify>
    ::template f<void, void, void, void>>();

  ut::same<int, partial<identity, identity, foo>::template f<void, void>>();

  test_context<partial<listify>, smp::partial<smp::listify>>()
    .test<list<>>()
    .test<seq_0, _0>()
    ;

  test_context<
    partial<inc<>, dec<>, listify>,
    smp::partial<smp::inc<>, smp::dec<>, smp::listify>
  >()
    .test<list<_1, _3>, _0, _4>()
    .test<list<_1, _3, _2>, _0, _4, _2>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  test_context<
    partial<inc<>, inc<>, inc<>, inc<>, listify>,
    smp::partial<smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::listify>
  >()
    .test<list<_2, _2, _2, _2>, _1, _1, _1, _1>()
    .test<list<_2, _2, _2, _2, _1, _3>, _1, _1, _1, _1, _1, _3>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    .not_invocable<_0, _0, _0>()
    ;

  ut::not_invocable<smp::partial<bad_function>>();
  ut::not_invocable<smp::partial<bad_function, bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial<identity, identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::lift<smp::partial>>();
}

TEST_SUITE_END()
