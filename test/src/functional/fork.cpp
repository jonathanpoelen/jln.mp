#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/fork.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

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

  test_context<fork<inc<>, dec<>, listify>, smp::fork<smp::inc<>, smp::dec<>, smp::listify>>()
    .test<list<_2, _0>, _1>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    ;
}

TEST_SUITE_END()
