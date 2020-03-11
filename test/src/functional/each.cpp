#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/function.hpp"
#include "jln/mp/smp/functional/each.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

struct foo
{
  template<class, class, class, class>
  using f = int;
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using yes = always<true_>;
  using no = always<false_>;

  test_pack2<each>();
  test_pack2<each, yes, yes>();
  test_pack2<each, yes, no>();
  test_pack2<each, yes>();

  ut::same<int, each<identity, identity, identity, identity, foo>
    ::template f<void, void, void, void>>();

  test_context<each<listify>, smp::each<smp::listify>>()
    .test<list<>>()
    .not_invocable<_1>()
    ;
  
  test_context<each<inc<>, dec<>, listify>, smp::each<smp::inc<>, smp::dec<>, smp::listify>>()
    .test<list<_1, _3>, _0, _4>()
    .not_invocable<>()
    .not_invocable<_0>()
    .not_invocable<_0, _0, _0>()
    ;

  test_context<
    each<inc<>, inc<>, inc<>, inc<>, listify>,
    smp::each<smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::listify>
  >()
    .test<list<_2, _2, _2, _2>, _1, _1, _1, _1>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    ;

  ut::not_invocable<smp::each<
    smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, foo
  >, _1, _1, _1, _1, _1>();

  ut::not_invocable<smp::each<bad_function>>();
  ut::not_invocable<smp::each<bad_function, bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::each<identity, identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::cfe<smp::each>>();
}

TEST_SUITE_END()
