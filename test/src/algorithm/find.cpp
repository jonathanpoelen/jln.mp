#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/find.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/algorithm/iota.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<find>();

  ut::same<seq_1_2_3, emp::find_if<seq_0_1_2_3, identity>>();

  ut::invoke_r<list<_12, _13>, iota<find<_12>>, _0, _14>();
  ut::invoke_r<list<_20, _21>, iota<find<_20>>, _0, _22>();
  ut::invoke_r<list<_60, _61>, iota<find<_60>>, _0, _62>();
  ut::invoke_r<list<_70, _71>, iota<find<_70>>, _0, _72>();
  ut::invoke_r<list<_130, _131>, iota<find<_130>>, _0, _132>();
  ut::invoke_r<list<_260, _261>, iota<find<_260>>, _0, _262>();
  ut::invoke_r<list<_320, _321>, iota<find<_320>>, _0, _322>();
  ut::invoke_r<list<_520, _521>, iota<find<_520>>, _0, _522>();
  ut::invoke_r<list<_555, _556>, iota<find<_555>>, _0, _557>();
  ut::invoke_r<list<_580, _581>, iota<find<_580>>, _0, _582>();
  ut::invoke_r<list<_780, _781>, iota<find<_780>>, _0, _782>();

  test_context<find_if<identity>, smp::find_if<smp::identity>>()
    .test<list<>>()
    .test<list<>, _0>()
    .test<seq_1, _1>()
    .test<seq_1, _0, _1>()
    .test<seq_1_2, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _1, _2>()
    .test<seq_1_2, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _1, _2>()
    .not_invocable<void>()
    ;

  test_context<
    find<_3, listify, always<void>>,
    smp::find<_3, smp::listify, smp::always<void>>,
    0
  >()
    .test<void>()
    .test<void, _0>()
    .test<void, _0, _1, _2>()
    .test<seq_3_2, _3, _2>()
    .test<seq_3_2, _0, _3, _2>()
    ;

  test_context<smp::find_if<equal_than<_3>>, void>()
    .test<seq_3_2, _0, _3, _2>()
    .test<list<_3, _2, bad_number>, _0, _3, _2, bad_number>()
    .not_invocable<bad_number>()
    .not_invocable<_0, bad_number>()
    ;
}

TEST_SUITE_END()
