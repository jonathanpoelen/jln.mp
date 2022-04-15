#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/collapse.hpp"
#include "jln/mp/number/numbers.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<collapse, emp::numbers<1, 0, 1>>();

  using keys = emp::numbers<0, 0, 2, 2, 2, 0, 1, 0, 2, 2>;
  using result = list<list<_0, _1>, list<_2, _3, _4>, list<_5>, list<_6>, list<_7>, list<_8, _9>>;

  ut::same<result, emp::collapse<seq_0_1_2_3_4_5_6_7_8_9, keys>>();

  test_context<collapse<keys>, smp::collapse<keys>>()
    .test<result, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .not_invocable<>()
    .not_invocable<list<>>()
    .not_invocable<seq_0_1>()
    .not_invocable<emp::numbers<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10>>()
    ;

  test_context<collapse<seq_0>, smp::collapse<seq_0>>()
    .test<list<list<int>>, int>()
    .not_invocable<>()
    .not_invocable<int, int>()
    ;

  test_context<collapse<list<>>, smp::collapse<list<>>>()
    .test<list<>>()
    .not_invocable<_0>()
    ;

  ut::not_invocable<smp::collapse<int>>();
  ut::not_invocable<smp::collapse<list<>, bad_function>>();
  ut::not_invocable<smp::collapse<seq_0_1, bad_function>, _0, _1>();
}

TEST_SUITE_END()

