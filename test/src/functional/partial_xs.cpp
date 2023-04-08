#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/functional/partial_xs.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/list/at.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<partial_xs>();
  test_mulary_pack<partial_xs, identity>();
  test_mulary_pack<partial_xs, identity, identity>();
  test_mulary_pack<partial_xs, identity, identity, identity>();

  ut::same<list<seq_0_1_2_3, seq_0_1_2_3, _2, _3>, partial_xs<listify, listify, listify>
    ::f<_0, _1, _2, _3>>();

  ut::same<list<seq_0_1, seq_0_1>, partial_xs<listify, listify, ut::binary>::f<_0, _1>>();

  test_context<partial_xs<listify>, smp::partial_xs<smp::listify>>()
    .test<list<>>()
    .test<seq_0, _0>()
    ;

  test_context<
    partial_xs<at0<inc<>>, at1<dec<>>, listify>,
    smp::partial_xs<smp::at0<smp::inc<>>, smp::at1<smp::dec<>>, smp::listify>
  >()
    .test<list<_1, _3>, _0, _4>()
    .test<list<_1, _3, _2>, _0, _4, _2>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  test_context<
    partial_xs<at0<inc<>>, at1<inc<>>, at2<inc<>>, at3<inc<>>, listify>,
    smp::partial_xs<smp::at0<smp::inc<>>, smp::at1<smp::inc<>>, smp::at2<smp::inc<>>, smp::at3<smp::inc<>>, smp::listify>
  >()
    .test<list<_2, _2, _2, _2>, _1, _1, _1, _1>()
    .test<list<_2, _2, _2, _2, _1, _3>, _1, _1, _1, _1, _1, _3>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    .not_invocable<_0, _0, _0>()
    ;

  test_context<
    partial_xs<
      at0<inc<>>, at1<inc<>>, at2<inc<>>, at3<inc<>>,
      at4<inc<>>, at5<inc<>>, at6<inc<>>, at7<inc<>>,
      at8<inc<>>, at9<inc<>>, listify>,
    smp::partial_xs<
      smp::at0<smp::inc<>>, smp::at1<smp::inc<>>, smp::at2<smp::inc<>>, smp::at3<smp::inc<>>,
      smp::at4<smp::inc<>>, smp::at5<smp::inc<>>, smp::at6<smp::inc<>>, smp::at7<smp::inc<>>,
      smp::at8<smp::inc<>>, smp::at9<smp::inc<>>, smp::listify>
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

  test_context<partial_xs<listify>, smp::partial_xs<smp::listify>>()
    .test<list<>>()
    .test<seq_0, _0>()
    ;

  test_context<
    partial_xs<listify, listify, listify, listify>,
    smp::partial_xs<smp::listify, smp::listify, smp::listify, smp::listify>
  >()
    .test<list<seq_0, list<>, list<>>, _0>()
    .test<list<seq_0_1, seq_0_1, list<>>, _0, _1>()
    .test<list<seq_0_1_2, seq_0_1_2, seq_0_1_2>, _0, _1, _2>()
    .test<list<seq_0_1_2_3, seq_0_1_2_3, seq_0_1_2_3, _3>, _0, _1, _2, _3>()
    ;

  ut::not_invocable<smp::partial_xs<smp::always<na>, smp::listify>>();
  ut::not_invocable<smp::partial_xs<bad_function>>();
  ut::not_invocable<smp::partial_xs<bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_xs<identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::partial_xs<identity, identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::lift<smp::partial_xs>>();
}

TEST_SUITE_END()
