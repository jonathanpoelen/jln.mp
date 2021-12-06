#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/if.hpp"
#include "jln/mp/smp/list/listify.hpp"
#include "jln/mp/smp/list/front.hpp"
#include "jln/mp/number/number.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<if_, _0>();
  test_pack2<if_, _0, _0>();

  test_context<
    if_<identity, always<int>>,
    smp::if_<smp::identity, smp::always<int>>
  >()
    .test<int, _3>()
    .test<_0, _0>()
    .not_invocable<>()
    .not_invocable<bad_number>()
    ;

  test_context<
    if_<front<>, always<int>>,
    smp::if_<smp::front<>, smp::always<int>>
  >()
    .test<int, _3>()
    .test<_0, _0>()
    .test<int, _3, _0>()
    .test<_0, _0, _3>()
    .not_invocable<>()
    .not_invocable<bad_number>()
    ;

  ut::not_invocable<smp::if_<smp::always<na>, smp::listify, smp::listify>>();
  ut::not_invocable<smp::if_<always<_1>, bad_function>>();
  ut::not_invocable<smp::if_<always<_0>, bad_function, bad_function>>();
  ut::not_invocable<smp::if_<always<void>, listify>>();
  ut::not_invocable<smp::if_<bad_function, bad_function, bad_function>>();
}

TEST_SUITE_END()
