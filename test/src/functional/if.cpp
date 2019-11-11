#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/if.hpp"
#include "jln/mp/smp/list/front.hpp"
#include "jln/mp/number/number.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<if_>()
    .test_binary<_1>()
    .test_binary<_1, _1>()
    .test_binary<_0, _0>()
    .test_unary<_1>()
    .test_unary<_1, _1>()
    .test_unary<_0, _0>()
  ;

  test_context<
    if_<identity, always<_1>>,
    smp::if_<smp::identity, smp::always<_1>>
  >()
    .test<_1, _3>()
    .test<_0, _0>()
    .not_invocable<>()
    .not_invocable<bad_number>()
    ;

  test_context<
    if_<front<>, always<_1>>,
    smp::if_<smp::front<>, smp::always<_1>>
  >()
    .test<_1, _3>()
    .test<_0, _0>()
    .not_invocable<>()
    .not_invocable<bad_number>()
    ;
}

TEST_SUITE_END()
