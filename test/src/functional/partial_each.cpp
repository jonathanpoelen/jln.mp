#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/functional/partial_each.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<partial_each>();
  test_unary_pack<partial_each, identity>();

  ut::same<list<seq_0, seq_1, _2, _3>, partial_each<listify, listify, listify>
    ::f<_0, _1, _2, _3>>();

  ut::same<seq_0_1, partial_each<identity, identity, ut::binary>::f<_0, _1>>();
  ut::same<seq_0_1, partial_each<identity, ut::binary>::f<_0, _1>>();

  test_context<partial_each<listify>, smp::partial_each<smp::listify>>()
    .test<list<>>()
    .test<seq_0, _0>()
    ;

  test_context<
    partial_each<inc<>, dec<>, listify>,
    smp::partial_each<smp::inc<>, smp::dec<>, smp::listify>
  >()
    .test<list<_1, _3>, _0, _4>()
    .test<list<_1, _3, _2>, _0, _4, _2>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  ut::not_invocable<smp::partial_each<smp::always<na>, smp::listify>>();
  ut::not_invocable<smp::partial_each<bad_function>>();
  ut::not_invocable<smp::partial_each<bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_each<identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_each<identity, identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::lift<smp::partial_each>>();
}

TEST_SUITE_END()
