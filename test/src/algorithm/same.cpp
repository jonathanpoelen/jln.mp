#include "test.hpp"

#include "jln/mp/smp/algorithm/same.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  ut::same<true_, emp::same<list<int, int, int>>>();
  ut::same<false_, emp::same<list<int, int, void>>>();

  test_pack<same>().test_unary();
  test_pack3<same>();

  test_context<same<>, smp::same<>>()
    .test<true_>()
    .test<true_, int>()
    .test<true_, int, int>()
    .test<true_, int, int, int>()
    .test<false_, int, void>()
    .test<false_, int, int, void>()
    ;

  ut::not_invocable<smp::same<bad_function>>();
  ut::not_invocable<smp::same<bad_function>, void>();
  ut::not_invocable<smp::same<bad_function>, void, void>();
  ut::not_invocable<smp::same<bad_function>, void, void, void>();
}

TEST_SUITE_END()
