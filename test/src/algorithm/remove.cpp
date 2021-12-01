#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/remove.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack3<remove_if, is<int>>();
  test_pack3<remove_if, void>();

  ut::same<emp::numbers<1, 2>, emp::remove_if<seq_0_1_2, is<_0>>>();
  ut::same<emp::numbers<0, 2>, emp::remove<seq_0_1_2, _1>>();

  test_context<
    remove_if<is<_1>>,
    smp::remove_if<is<_1>>,
    0
  >()
    .test<list<>>()
    .test<seq_0_0_0, _0, _0, _0>()
    .test<list<>, _1, _1, _1>()
    .test<emp::numbers<0, 3>, _0, _1, _3>()
    ;

  test_context<
    remove_if<always<na>>,
    smp::remove_if<always<na>>,
    0
  >()
    .test<list<>>()
    .not_invocable<_0, _0, _0>()
    .not_invocable<_0, _1, _3>()
    ;

  test_context<remove<_1>, smp::remove<_1>, 0>()
    .test<list<>>()
    .test<seq_0_0_0, _0, _0, _0>()
    .test<list<>, _1, _1, _1>()
    .test<emp::numbers<0, 3>, _0, _1, _3>()
    ;

  ut::not_invocable<smp::remove<void, bad_function>>();
  ut::not_invocable<smp::remove<void, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::remove_if<bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::remove_if<always<void>>, _1, _1, _1>();
  ut::not_invocable<smp::remove_if<bad_function, bad_function>>();
  ut::not_invocable<smp::remove_if<bad_function, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
