#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/starts_with.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using l0 = list<>;
  using l1 = list<_1>;
  using l2 = list<_1, _2>;

  test_pack3<starts_with, l0>();
  test_pack3<starts_with>();
  test_pack<starts_with, l1>().test_unary();
  test_pack<starts_with, l2>().test_unary();

  test_context<starts_with<l0>, smp::starts_with<l0>>()
    .test<_1>()
    .test<_1, _0>()
    ;

  test_context<starts_with<l1>, smp::starts_with<l1>>()
    .test<_0>()
    .test<_0, _0>()
    .test<_0, _2>()
    .test<_0, _0, _1>()
    .test<_1, _1, _2>()
    ;

  test_context<starts_with<l2>, smp::starts_with<l2>>()
    .test<_0>()
    .test<_0, _0>()
    .test<_0, _0, _1>()
    .test<_0, _0, _1, _2>()
    .test<_0, _0, _1, _2, _3>()
    .test<_1, _1, _2, _3>()
    .test<_1, _1, _2>()
    ;

  test_context<starts_with<int>, smp::starts_with<int>>()
    .not_invocable<>()
    .not_invocable<int>()
    ;

  ut::not_invocable<smp::starts_with<int>>();
  ut::not_invocable<smp::starts_with<l0, bad_function>>();
}

TEST_SUITE_END()
