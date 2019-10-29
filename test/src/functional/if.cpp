#include "test.hpp"

#include "jln/mp/functional/if.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  using yes = always<true_>;
  using no = always<false_>;

  test_pack<if_>()
    .test_binary<yes>()
    .test_binary<yes, yes>()
    .test_binary<no, no>()
    .test_unary<yes>()
    .test_unary<yes, yes>()
    .test_unary<no, no>()
  ;

  test_context<
    if_<identity, yes>,
    smp::if_<smp::identity, smp::always<true_>, smp::always<false_>>
  >()
    .test<true_, number<3>>()
    .test<false_, number<0>>()
    .not_invocable<yes>()
    ;
}

TEST_SUITE_END()
