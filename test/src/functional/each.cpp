#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/lift.hpp"
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

  test_mulary_pack<each>();
  test_mulary_pack<each, identity>();
  test_mulary_pack<each, identity, identity>();
  test_mulary_pack<each, identity, identity, identity>();

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

  ut::not_invocable<smp::each<smp::always<na>, smp::listify>, _1>();
  ut::not_invocable<smp::each<bad_function>>();
  ut::not_invocable<smp::each<bad_function, bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::each<identity, identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::lift<smp::each>>();
}

TEST_SUITE_END()
