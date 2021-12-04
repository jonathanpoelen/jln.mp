#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/functional/tee.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

struct foo
{
  template<class, class, class, class>
  using f = int;
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using yes = always<true_>;
  using no = always<false_>;

  test_pack3<tee, yes, yes>();
  test_pack3<tee, yes, no>();
  test_pack3<tee, yes>();

  ut::same<int, tee<identity, identity, identity, identity, foo>::template f<void>>();

  test_context<tee<inc<>, dec<>, listify>, smp::tee<smp::inc<>, smp::dec<>, smp::listify>>()
    .test<list<_2, _0>, _1>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    ;

  test_context<
    tee<inc<>, inc<>, inc<>, inc<>, listify>,
    smp::tee<smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::listify>
  >()
    .test<list<_2, _2, _2, _2>, _1>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    ;

  test_context<tee<listify>, smp::tee<smp::listify>>()
    .test<list<>>()
    .test<list<>, _1>()
    ;

  ut::not_invocable<smp::tee<
    smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, foo
  >, _1>();

  ut::not_invocable<smp::tee<smp::always<na>, smp::listify>>();
  ut::not_invocable<smp::tee<bad_function>>();
  ut::not_invocable<smp::tee<bad_function, bad_function, bad_function, bad_function, listify>>();
  ut::not_invocable<smp::tee<bad_function, bad_function, bad_function, bad_function, bad_function>>();
  ut::not_invocable<smp::tee<bad_function, listify>>();
  ut::not_invocable<smp::tee<bad_function, bad_function>>();
  ut::not_invocable<smp::tee<bad_function, bad_function, listify>>();
  ut::not_invocable<smp::tee<bad_function, bad_function, bad_function>>();
  ut::not_invocable<smp::tee<bad_function, bad_function, bad_function, listify>>();
  ut::not_invocable<smp::tee<bad_function, bad_function, bad_function, bad_function>>();
  ut::not_invocable<smp::lift<smp::tee>>();
}

TEST_SUITE_END()
