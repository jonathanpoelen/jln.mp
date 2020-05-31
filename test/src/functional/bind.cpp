#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/bind.hpp"
#include "jln/mp/smp/list/push_front.hpp"
#include "jln/mp/smp/list/pop_front.hpp"
#include "jln/mp/smp/list/listify.hpp"

TEST_SUITE_BEGIN()

struct foo
{
  template<class, class>
  using f = int;
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<bind>();
  test_pack2<bind1st, listify>();
  test_pack2<bind2nd, listify>();

  ut::same<void, bind1st<identity, identity>::template f<void>>();
  ut::same<list<int, void>, bind1st<always<int>, listify>::template f<void, void>>();
  ut::same<list<int, void, char, long>, bind<listify, int, void>::template f<char, long>>();
  ut::same<list<char, long, int, void>, reverse_bind<listify, int, void>::template f<char, long>>();

  test_context<
    bind<pop_front<>, int, long>,
    smp::bind<smp::pop_front<>, int, long>
  >()
    .test<list<long>>()
    .test<list<long, void, char>, void, char>()
    ;

  ut::not_invocable<smp::bind<smp::pop_front<>>>();

  test_context<
    reverse_bind<pop_front<>, int, long>,
    smp::reverse_bind<smp::pop_front<>, int, long>
  >()
    .test<list<long>>()
    .test<list<char, int, long>, void, char>()
    ;

  ut::not_invocable<smp::reverse_bind<smp::pop_front<>>>();

  test_context<
    bind1st<push_front<_9>, listify>,
    smp::bind1st<smp::push_front<_9>, smp::listify>
  >()
    .test<list<list<_9, _0>>, _0>()
    .test<list<list<_9, _0>, seq_0_0, seq_0_0_0>, _0, seq_0_0, seq_0_0_0>()
    .not_invocable<>()
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
