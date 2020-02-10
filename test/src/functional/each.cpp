#include "test.hpp"
#include "test/numbers.hpp"

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

  test_pack<each>()
    .test_binary<yes, yes>()
    .test_binary<no, no>()
    .test_unary<yes>()
  ;

  ut::same<int, each<identity, identity, identity, identity, foo>
    ::template f<void, void, void, void>>();

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
}

TEST_SUITE_END()
