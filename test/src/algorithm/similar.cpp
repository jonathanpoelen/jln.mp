#include "test.hpp"

#include "jln/mp/smp/algorithm/similar.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  ut::same<true_, emp::similar<list<int, int, int>>>();
  ut::same<true_, emp::similar<list<list<>, list<int>, list<char, short>>>>();
  ut::same<false_, emp::similar<list<int, int, void>>>();

  test_unary_pack<similar>();

  test_context<similar<>, smp::similar<>>()
    .test<true_>()
    .test<true_, int>()
    .test<true_, int, int>()
    .test<true_, int, int, int>()
    .test<true_, list<>>()
    .test<true_, list<>, list<>>()
    .test<true_, list<>, list<int>>()
    .test<false_, int, void>()
    .test<false_, int, int, void>()
    .test<false_, int, int, list<int>>()
    .test<false_, similar<>, list<>>()
    ;

  ut::not_invocable<smp::similar<bad_function>>();
  ut::not_invocable<smp::similar<bad_function>, void>();
  ut::not_invocable<smp::similar<bad_function>, void, void>();
  ut::not_invocable<smp::similar<bad_function>, void, void, void>();
}

TEST_SUITE_END()
