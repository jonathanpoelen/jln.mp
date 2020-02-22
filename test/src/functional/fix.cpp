#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/fix.hpp"
#include "jln/mp/smp/utility/conditional.hpp"

TEST_SUITE_BEGIN()

struct foo
{
  template<class F, class x, class... xs>
  using f = typename jln::mp::conditional_c<1 < x::value>
    ::template f<F, jln::mp::listify>
    ::template f<number<x::value - 1>, x, xs...>;
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<fix>();

  ut::same<seq_0_1_2, emp::fix<foo, _2>>();

  test_context<fix<foo>, smp::fix<subcontract_barrier<foo>>, -1>()
    .test<seq_0_1, _1>()
    .not_invocable<>()
    ;
}

TEST_SUITE_END()
