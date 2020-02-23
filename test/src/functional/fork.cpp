#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/fork.hpp"
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

  test_pack<fork>()
    .test_binary<yes, yes>()
    .test_binary<no, no>()
    .test_unary<yes>()
  ;

  ut::same<int, fork<identity, identity, identity, identity, foo>::template f<void>>();

  test_context<fork<inc<>, dec<>, listify>, smp::fork<smp::inc<>, smp::dec<>, smp::listify>>()
    .test<list<_2, _0>, _1>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    ;

  test_context<
    fork<inc<>, inc<>, inc<>, inc<>, listify>,
    smp::fork<smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::listify>
  >()
    .test<list<_2, _2, _2, _2>, _1>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    ;

  ut::not_invocable<smp::fork<
    smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, foo
  >, _1>();

  ut::not_invocable<smp::fork<bad_function, bad_function, bad_function, bad_function, listify>>();
  ut::not_invocable<smp::fork<bad_function, bad_function, bad_function, bad_function, bad_function>>();
  ut::not_invocable<smp::fork<bad_function, listify>>();
  ut::not_invocable<smp::fork<bad_function, bad_function>>();
  ut::not_invocable<smp::fork<bad_function, bad_function, listify>>();
  ut::not_invocable<smp::fork<bad_function, bad_function, bad_function>>();
  ut::not_invocable<smp::fork<bad_function, bad_function, bad_function, listify>>();
  ut::not_invocable<smp::fork<bad_function, bad_function, bad_function, bad_function>>();
}

TEST_SUITE_END()
