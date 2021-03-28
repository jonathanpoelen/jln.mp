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
  test_pack2<find_if, identity>();

  ut::same<seq_1_2_3, emp::find_if<seq_0_1_2_3, identity>>();

  ut::invoke_r<list<_12, _13>, iota<find<_12>>, _0, _14>();
  ut::invoke_r<list<_20, _21>, iota<find<_20>>, _0, _22>();
  ut::invoke_r<list<_60, _61>, iota<find<_60>>, _0, _62>();
  ut::invoke_r<list<_70, _71>, iota<find<_70>>, _0, _72>();
  ut::invoke_r<list<number<130>, number<131>>, iota<find<number<130>>>, _0, number<132>>();
  ut::invoke_r<list<number<260>, number<261>>, iota<find<number<260>>>, _0, number<262>>();
  ut::invoke_r<list<number<320>, number<321>>, iota<find<number<320>>>, _0, number<322>>();
  ut::invoke_r<list<number<520>, number<521>>, iota<find<number<520>>>, _0, number<522>>();
  ut::invoke_r<list<number<555>, number<556>>, iota<find<number<555>>>, _0, number<557>>();
  ut::invoke_r<list<number<580>, number<581>>, iota<find<number<580>>>, _0, number<582>>();
  ut::invoke_r<list<number<780>, number<781>>, iota<find<number<780>>>, _0, number<782>>();

  test_context<find_if<identity>, smp::find_if<smp::identity>>()
    .test<list<>>()
    .test<list<>, _0>()
    .test<seq_1, _1>()
    .test<seq_1, _0, _1>()
    .test<seq_1, _0, _0, _1>()
    .test<seq_1_2, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _1, _2>()
    .test<seq_1_2, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _1, _2>()
    .not_invocable<void>()
    .not_invocable<_0, void>()
    ;

  test_context<find_if_not<identity>, smp::find_if_not<smp::identity>, 0>()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<list<>, _1>()
    .test<seq_0_1, _0, _1>()
    .test<list<_0, _0, _1>, _0, _0, _1>()
    .test<list<_0, _0, _1>, _1, _0, _0, _1>()
    .not_invocable<void>()
    .not_invocable<_1, void>()
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

  test_context<smp::find_if<equal_to<_3>>, void>()
    .test<seq_3_2, _0, _3, _2>()
    .test<list<_3, _2, bad_number>, _0, _3, _2, bad_number>()
    .not_invocable<bad_number>()
    .not_invocable<_0, bad_number>()
    ;

  ut::not_invocable<smp::find<_1, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::find_if<void>, _1, _1, _1>();
  ut::not_invocable<smp::find_if<always<void>>, _1, _1, _1>();
  ut::not_invocable<smp::find_if<always<_1>, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::find_if<bad_function, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
