#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/fold_left.hpp"
#include "jln/mp/smp/list/pop_front.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<list<list<list<_0, _1>, _2>, _3>,
    emp::fold_left<seq_1_2_3, _0, listify>>();

  test_pack3<fold_left>();
  test_pack3<fold_left, listify>();

  test_pack<fold_left>()
    .test_variadic()
    .test_binary()
  ;
  test_pack<fold_left, listify>()
    .test_variadic()
    .test_unary()
  ;

  test_context<fold_left<listify>, smp::fold_left<smp::listify>>()
    .test<_0, _0>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<list<list<_0, _1>, _2>, _3>, _0, _1, _2, _3>()
    .test<list<list<list<list<list<_0, _1>, _2>, _3>, _4>, _5>,
      _0, _1, _2, _3, _4, _5>()
    .not_invocable<>()
    ;

  test_context<
    fold_left<pop_front<identity>>,
    smp::fold_left<smp::pop_front<smp::identity>>
  >()
    .test<_0, _0>()
    .test<_1, _0, _1>()
    .test<_3, _0, _1, _2, _3>()
    .not_invocable<>()
    .not_invocable<na>()
    .not_invocable<_0, na>()
    .not_invocable<_0, _1, na>()
    ;

  ut::not_invocable<smp::fold_left<listify, bad_function>, _1>();
  ut::not_invocable<smp::fold_left<listify, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::fold_left<bad_function, bad_function>, _1>();
  ut::not_invocable<smp::fold_left<bad_function, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
