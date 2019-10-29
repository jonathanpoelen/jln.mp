#include "test.hpp"

#include "jln/mp/functional/fork.hpp"
#include "jln/mp/number/operators.hpp"
#include "jln/mp/number/numbers.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  using yes = always<true_>;
  using no = always<false_>;

  test_pack<fork>()
    .test_binary<yes, yes>()
    .test_binary<no, no>()
    .test_unary<yes>()
  ;

  using f = fork<inc<>, dec<>, listify>;

  test_context<f, sfinae<f>>()
    .test<emp::numbers<1, 3>, number<0>, number<4>>()
    .not_invocable<number<0>>()
    .not_invocable<number<0>, number<0>, number<0>>()
    ;
}

TEST_SUITE_END()
