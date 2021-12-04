#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/functional/on.hpp"
#include "jln/mp/smp/number/operators.hpp"

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

  using yes = always<true_>;
  using no = always<false_>;

  test_pack2<on>();
  test_pack2<on, yes, yes>();
  test_pack2<on, yes, no>();
  test_pack2<on, yes>();

  test_pack2<on>();
  test_pack2<on, yes, yes>();
  test_pack2<on, yes, no>();
  test_pack2<on, yes>();

  ut::same<list<list<void>, list<void>, void, void>, on<listify, listify, listify>
    ::template f<void, void, void, void>>();

  ut::same<int, on<identity, identity, foo>::template f<void, void>>();

  test_context<on<listify>, smp::on<smp::listify>>()
    .test<list<>>()
    .test<seq_0, _0>()
    ;

  test_context<
    on<inc<>, dec<>, listify>,
    smp::on<smp::inc<>, smp::dec<>, smp::listify>
  >()
    .test<list<_1, _3>, _0, _4>()
    .test<list<_1, _3, _2>, _0, _4, _2>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  test_context<
    on<inc<>, inc<>, inc<>, inc<>, listify>,
    smp::on<smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::listify>
  >()
    .test<list<_2, _2, _2, _2>, _1, _1, _1, _1>()
    .test<list<_2, _2, _2, _2, _1, _3>, _1, _1, _1, _1, _1, _3>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    .not_invocable<_0, _0, _0>()
    ;

  test_context<on<listify>, smp::on<smp::listify>>()
    .test<list<>>()
    .test<seq_0, _0>()
    ;

  test_context<
    on<listify, listify, listify>,
    smp::on<smp::listify, smp::listify, smp::listify>
  >()
    .test<list<seq_0, list<>>, _0>()
    .test<list<seq_0, seq_0>, _0, _0>()
    .test<list<seq_0, seq_0, _0>, _0, _0, _0>()
    ;

  test_context<
    on<inc<>, dec<>, listify>,
    smp::on<smp::inc<>, smp::dec<>, smp::listify>
  >()
    .test<list<_1, _3>, _0, _4>()
    .not_invocable<list<_1, _3, _2>, _0, _4, _2>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  test_context<
    on<inc<>, inc<>, inc<>, inc<>, listify>,
    smp::on<smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::listify>
  >()
    .test<list<_2, _2, _2, _2>, _1, _1, _1, _1>()
    .test<list<_2, _2, _2, _2, _1>, _1, _1, _1, _1, _1>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    .not_invocable<_0, _0, _0>()
    ;

  ut::not_invocable<smp::on<smp::always<na>, smp::listify>>();
  ut::not_invocable<smp::on<bad_function>>();
  ut::not_invocable<smp::on<bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::on<identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::on<identity, identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::lift<smp::on>>();
}

TEST_SUITE_END()
