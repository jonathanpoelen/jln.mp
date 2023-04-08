#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/functional/partial_tee.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<partial_tee>();
  test_unary_pack<partial_tee, identity>();

  ut::same<list<seq_0_1_2_3, seq_0_1_2_3, _2, _3>, partial_tee<listify, listify, listify>
    ::f<_0, _1, _2, _3>>();

  ut::same<list<seq_0_1, seq_0_1>, partial_tee<listify, listify, ut::binary>::f<_0, _1>>();
  ut::same<list<seq_0_1, _1>, partial_tee<listify, ut::binary>::f<_0, _1>>();
  ut::same<seq_0, partial_tee<identity, listify>::f<_0>>();

  test_context<partial_tee<listify>, smp::partial_tee<smp::listify>>()
    .test<list<>>()
    .test<seq_0, _0>()
    ;

  test_context<
    partial_tee<size<>, size<>, listify>,
    smp::partial_tee<smp::size<>, smp::size<>, smp::listify>
  >()
    .test<list<_2, _2>, _0, _4>()
    .test<list<_3, _3, _2>, _0, _4, _2>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  ut::not_invocable<smp::partial_tee<smp::always<na>, smp::listify>>();
  ut::not_invocable<smp::partial_tee<bad_function>>();
  ut::not_invocable<smp::partial_tee<bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee<identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_tee<identity, identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::lift<smp::partial_tee>>();
}

TEST_SUITE_END()
