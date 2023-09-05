#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/apply_or_identity.hpp"
#include "jln/mp/smp/utility/is.hpp"
#include "jln/mp/smp/list/listify.hpp"
#include "jln/mp/smp/list/front.hpp"
#include "jln/mp/number/number.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<apply_or_identity, _0>();

  test_context<
    apply_or_identity<identity, always<int>>,
    smp::apply_or_identity<smp::identity, smp::always<int>>
  >()
    .test<int, _3>()
    .test<_0, _0>()
    .not_invocable<>()
    .not_invocable<bad_number>()
    ;

  test_context<
    apply_or_identity<is<_2>, always<int>>,
    smp::apply_or_identity<smp::is<_2>, smp::always<int>>
  >()
    .test<_0, _0>()
    .test<_1, _1>()
    .test<int, _2>()
    .test<_3, _3>()
    .not_invocable<>()
    ;

  ut::not_invocable<smp::apply_or_identity<smp::always<na>, smp::listify>>();
  ut::not_invocable<smp::apply_or_identity<always<_1>, bad_function>>();
  ut::not_invocable<smp::apply_or_identity<always<void>, listify>>();
  ut::not_invocable<smp::apply_or_identity<bad_function, bad_function>>();
}

TEST_SUITE_END()
