#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/scan_left.hpp"
#include "jln/mp/smp/list/pop_front.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<
    list<
      _0,
      list<_0, _1>,
      list<list<_0, _1>, _2>
    >,
    emp::scan_left<seq_0_1_2, listify>
  >();

  test_pack2<scan_left, listify>();

  test_context<scan_left<listify>, smp::scan_left<smp::listify>>()
    .test<list<>>()
    .test<list<_0>, _0>()
    .test<list<_0, list<_0, _1>>, _0, _1>()
    .test<list<_0, list<_0, _1>, list<list<_0, _1>, _2>>, _0, _1, _2>()
    .test<list<
        _0,
        list<_0, _1>,
        list<list<_0, _1>, _2>,
        list<list<list<_0, _1>, _2>, _3>
      >,
      _0, _1, _2, _3>()
    .test<
      list<
        _0,
        list<_0, _1>,
        list<list<_0, _1>, _2>,
        list<list<list<_0, _1>, _2>, _3>,
        list<list<list<list<_0, _1>, _2>, _3>, _4>,
        list<list<list<list<list<_0, _1>, _2>, _3>, _4>, _5>,
        list<list<list<list<list<list<_0, _1>, _2>, _3>, _4>, _5>, _6>,
        list<list<list<list<list<list<list<_0, _1>, _2>, _3>, _4>, _5>, _6>, _7>,
        list<list<list<list<list<list<list<list<_0, _1>, _2>, _3>, _4>, _5>, _6>, _7>, _8>,
        list<list<list<list<list<list<list<list<list<_0, _1>, _2>, _3>, _4>, _5>, _6>, _7>, _8>, _9>,
        list<list<list<list<list<list<list<list<list<list<_0, _1>, _2>, _3>, _4>, _5>, _6>, _7>, _8>, _9>, _10>
      >,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>()
    ;

  test_context<
    scan_left<pop_front<identity>>,
    smp::scan_left<smp::pop_front<smp::identity>>
  >()
    .test<list<>>()
    .test<list<_0>, _0>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<_0, _1, _2, _3>, _0, _1, _2, _3>()
    .not_invocable<na>()
    .not_invocable<_0, na>()
    .not_invocable<_0, _1, na>()
    ;

  ut::not_invocable<smp::scan_left<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::scan_left<listify, bad_function>, _1>();
  ut::not_invocable<smp::scan_left<listify, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::scan_left<bad_function, bad_function>, _1>();
  ut::not_invocable<smp::scan_left<bad_function, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::scan_left<bad_function, bad_function>, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::scan_left<smp::add<>>, _1, _1, _1, _1, _1, void>();
  ut::not_invocable<smp::scan_left<smp::add<>>, void, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::scan_left<smp::add<>>,
    _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, void>();
  ut::not_invocable<smp::scan_left<smp::add<>>,
    void, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>();
}

TEST_SUITE_END()
