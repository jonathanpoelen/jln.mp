#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/is_sorted.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<is_sorted, listify>();

  ut::same<_1, emp::is_sorted<seq_0_1_2_3_4_5_6_7_8_9>>();

  test_context<is_sorted<>, smp::is_sorted<>>()
    .test<_1>()
    .test<_1, _0>()
    .test<_1, _0, _0>()
    .test<_1, _0, _1>()
    .test<_0, _1, _0>()
    .test<_1, _0, _1, _2>()
    .test<_0, _1, _0, _2>()
    .test<_0, _0, _2, _1>()
    .test<_1, _0, _1, _2, _3, _4>()
    .test<_0, _0, _1, _2, _4, _3>()
    .test<_1, bad_number>()
    .not_invocable<bad_number, bad_number>()
    .not_invocable<bad_number, bad_number, bad_number>()
    ;

  test_context<smp::is_sorted<na>, void>()
    .test<_1>()
    .not_invocable<_1, _2>()
    ;

  ut::not_invocable<smp::is_sorted<less<>, bad_function>, _1, _1>();
  ut::not_invocable<smp::is_sorted<less<>, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::is_sorted<always<void>>, _1, _1, _1>();
  ut::not_invocable<smp::is_sorted<always<void>, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::is_sorted<bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::is_sorted<bad_function, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
