#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/fold_left_xs.hpp"
#include "jln/mp/smp/list/front.hpp"
#include "jln/mp/smp/list/pop_front.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<list<list<list<_0, _1, _2, _3>, _2, _3>, _3>,
    emp::fold_left_xs<seq_1_2_3, _0, listify>>();

  ut::same<list<list<_0, _1, _3, _5, _7, _9>, _3, _5, _7, _9>,
    emp::partial_fold_left_xs_c<seq_1_3_5_7_9, 2, _0, listify>>();

  ut::same<list<list<list<list<_0, _1, _3, _5, _7, _9>, _3, _5, _7, _9>, _5, _7, _9>, _7, _9>,
    emp::partial_fold_left_xs_c<seq_1_3_5_7_9, -2, _0, listify>>();

  test_pack3<fold_left_xs>();
  test_pack3<fold_left_xs, listify>();

  test_pack<fold_left_xs>()
    .test_variadic()
    .test_binary()
    .test_unary()
  ;
  test_pack<fold_left_xs, listify>()
    .test_variadic()
    .test_unary()
  ;

  test_context<fold_left_xs<listify>, smp::fold_left_xs<smp::listify>>()
    .test<_0, _0>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<list<list<_0, _1, _2, _3>, _2, _3>, _3>, _0, _1, _2, _3>()
    .test<list<list<list<list<list<_0, _1, _2, _3, _4, _5>,
        _2, _3, _4, _5>, _3, _4, _5>, _4, _5>, _5>,
      _0, _1, _2, _3, _4, _5>()
    .not_invocable<>()
    ;

  test_context<
    fold_left_xs<pop_front<front<>>>,
    smp::fold_left_xs<smp::pop_front<smp::front<>>>
  >()
    .test<_0, _0>()
    .test<_1, _0, _1>()
    .test<_3, _0, _1, _2, _3>()
    .not_invocable<>()
    .not_invocable<na>()
    .not_invocable<_0, na>()
    .not_invocable<_0, _1, na>()
    ;

  ut::not_invocable<smp::fold_left_xs<listify, bad_function>, _1>();
  ut::not_invocable<smp::fold_left_xs<listify, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::fold_left_xs<bad_function, bad_function>, _1>();
  ut::not_invocable<smp::fold_left_xs<bad_function, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::fold_left_xs<bad_function, bad_function>, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::fold_left_xs<smp::add<>>, _1, _1, _1, _1, _1, void>();
  ut::not_invocable<smp::fold_left_xs<smp::add<>>, void, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::fold_left_xs<smp::add<>>,
    _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, void>();
  ut::not_invocable<smp::fold_left_xs<smp::add<>>,
    void, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>();
}

TEST_SUITE_END()
