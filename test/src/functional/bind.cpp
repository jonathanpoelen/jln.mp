#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/bind.hpp"
#include "jln/mp/smp/list/push_front.hpp"
#include "jln/mp/smp/list/list.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<bind1st, listify>()
    .test_variadic()
    .test_binary()
    .test_unary()
  ;

  ut::same<void, bind1st<identity, identity>::template f<void>>();
  ut::same<list<int, void>, bind1st<always<int>, listify>::template f<void, void>>();

  test_context<
    bind1st<push_front<_9>, listify>,
    smp::bind1st<smp::push_front<_9>, smp::listify>
  >()
    .test<list<list<_9, _0>>, _0>()
    .test<list<list<_9, _0>, seq_0_0, seq_0_0_0>, _0, seq_0_0, seq_0_0_0>()
    .not_invocable<>()
    ;


  test_pack<bind2nd, listify>()
    .test_variadic()
    .test_binary()
    .test_unary()
  ;

  ut::same<list<void, int>, bind2nd<always<int>, listify>::template f<void, void>>();

  test_context<
    bind2nd<push_front<_9>, listify>,
    smp::bind2nd<smp::push_front<_9>, smp::listify>
  >()
    .test<list<_1, list<_9, _0>>, _1, _0>()
    .test<list<seq_0_0, list<_9, _0>, seq_0_0_0>, seq_0_0, _0, seq_0_0_0>()
    .not_invocable<>()
    .not_invocable<void>()
    ;


  ut::not_invocable<smp::bind1st<push_front<int>, bad_function>>();
  ut::not_invocable<smp::bind1st<bad_function, bad_function>>();
  ut::not_invocable<smp::bind2nd<push_front<int>, bad_function>>();
  ut::not_invocable<smp::bind2nd<bad_function, bad_function>>();
}

TEST_SUITE_END()
