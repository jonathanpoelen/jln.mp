#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/is_unique.hpp"
#include "jln/mp/smp/functional/each.hpp"
#include "jln/mp/smp/list/at.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<is_unique>();

  ut::same<_1, emp::is_unique<emp::numbers<0, 1, 2>>>();
  ut::same<_0, emp::is_unique<emp::numbers<0, 1, 0, 2, 2>>>();

  test_context<is_unique<>, smp::is_unique<>>()
    .test<_1>()
    .test<_1, _0>()
    .test<_0, _0, _0>()
    .test<_1, _0, _1>()
    .test<_1, _0, _1, _2>()
    .test<_0, _0, _0, _0, _0, _0>()
    .test<_0, _0, _0, _1, _0, _2, _2, _2, _0, _0, _3>()
    ;

  using first = unpack<at0<>>;
  using smp_first = smp::unpack<smp::at0<>>;
  test_context<
    is_unique_if<each<first, first, cfe<std::is_same>>>,
    smp::is_unique_if<smp::each<smp_first, smp_first, smp::cfe<std::is_same>>>
  >()
    .test<_1>()
    .test<_1, _0>()
    .test<_0, list<_0, _0>, list<_0, _1>>()
    .test<_1, list<_0, _0>, list<_1, _0>>()
    .test<_0, list<_0, _0>, list<_0, _1>, list<_1, _0>>()
    .not_invocable<_0, _0>()
    ;

  test_context<is_unique_if<equal<>>, smp::is_unique_if<smp::equal<>>, 0>()
    .test<_1>()
    .test<_1, _1>()
    .test<_1, _1, _0>()
    .not_invocable<_1, _1, _0, void>()
    ;

  ut::not_invocable<smp::is_unique<bad_function>>();
  ut::not_invocable<smp::is_unique_if<always<void>, bad_function>>();
  ut::not_invocable<smp::is_unique_if<always<true_>, bad_function>>();
  ut::not_invocable<smp::is_unique_if<bad_function, bad_function>>();
  ut::not_invocable<smp::is_unique_if<bad_function, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
