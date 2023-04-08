#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/functional/partial.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<partial>();
  test_mulary_pack<partial, identity>();
  test_mulary_pack<partial, identity, identity>();
  test_mulary_pack<partial, identity, identity, identity>();

  ut::same<list<seq_0, seq_1, _2, _3>, partial<listify, listify, listify>
    ::f<_0, _1, _2, _3>>();

  ut::same<seq_0_1, partial<identity, identity, ut::binary>::f<_0, _1>>();

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

  test_context<
    partial<inc<>, inc<>, inc<>, inc<>, inc<>, inc<>, inc<>, inc<>, inc<>, inc<>, listify>,
    smp::partial<smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::listify>
  >()
    .test<list<_2, _2, _2, _2, _2, _2, _2, _2, _2, _2>, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>()
    .test<list<_2, _2, _2, _2, _2, _2, _2, _2, _2, _2, _1>, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>()
    .test<list<_2, _2, _2, _2, _2, _2, _2, _2, _2, _2, _1, _3>, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _3>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    .not_invocable<_0, _0, _0>()
    .not_invocable<_0, _0, _0, _0>()
    .not_invocable<_0, _0, _0, _0, _0>()
    .not_invocable<_0, _0, _0, _0, _0, _0>()
    .not_invocable<_0, _0, _0, _0, _0, _0, _0>()
    .not_invocable<_0, _0, _0, _0, _0, _0, _0, _0>()
    .not_invocable<_0, _0, _0, _0, _0, _0, _0, _0, _0>()
    ;

  test_context<partial<listify>, smp::partial<smp::listify>>()
    .test<list<>>()
    .test<seq_0, _0>()
    ;

  test_context<
    partial<listify, listify, listify, listify>,
    smp::partial<smp::listify, smp::listify, smp::listify, smp::listify>
  >()
    .test<list<seq_0, list<>, list<>>, _0>()
    .test<list<seq_0, seq_1, list<>>, _0, _1>()
    .test<list<seq_0, seq_1, seq_2>, _0, _1, _2>()
    .test<list<seq_0, seq_1, seq_2, _3>, _0, _1, _2, _3>()
    ;

  test_context<
    partial<inc<>, dec<>, listify>,
    smp::partial<smp::inc<>, smp::dec<>, smp::listify>
  >()
    .test<list<_1, _3>, _0, _4>()
    .not_invocable<list<_1, _3, _2>, _0, _4, _2>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  test_context<
    partial<inc<>, inc<>, inc<>, inc<>, listify>,
    smp::partial<smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::listify>
  >()
    .test<list<_2, _2, _2, _2>, _1, _1, _1, _1>()
    .test<list<_2, _2, _2, _2, _1>, _1, _1, _1, _1, _1>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    .not_invocable<_0, _0, _0>()
    ;

  ut::not_invocable<smp::partial<smp::always<na>, smp::listify>>();
  ut::not_invocable<smp::partial<bad_function>>();
  ut::not_invocable<smp::partial<bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial<identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial<identity, identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::lift<smp::partial>>();
}

TEST_SUITE_END()
