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
    .test<_1, int, int&, int&&, int const, int const&, int const&&>()
    .test<_0, int, int&, int&&, int const, int const&, int const&&, int&>()
    ;

  using first = unpack<at0<>>;
  using smp_first = smp::unpack<smp::at0<>>;
  test_context<
    is_unique_with<each<first, first, lift<std::is_same>>>,
    smp::is_unique_with<smp::each<smp_first, smp_first, smp::lift<std::is_same>>>
  >()
    .test<_1>()
    .test<_1, _0>()
    .test<_0, list<_0, _0>, list<_0, _1>>()
    .test<_1, list<_0, _0>, list<_1, _0>>()
    .test<_0, list<_0, _0>, list<_0, _1>, list<_1, _0>>()
    .not_invocable<_0, _0>()
    ;

  test_context<is_unique_with<equal<>>, smp::is_unique_with<smp::equal<>>>()
    .test<_1>()
    .test<_1, _1>()
    .test<_1, _1, _0>()
    .not_invocable<_1, _1, _0, void>()
    ;

  ut::not_invocable<smp::is_unique<bad_function>>();
  ut::not_invocable<smp::is_unique_with<always<void>>, _1, _1>();
  ut::not_invocable<smp::is_unique_with<always<void>, bad_function>>();
  ut::not_invocable<smp::is_unique_with<always<true_>, bad_function>>();
  ut::not_invocable<smp::is_unique_with<bad_function, bad_function>>();
  ut::not_invocable<smp::is_unique_with<bad_function, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
