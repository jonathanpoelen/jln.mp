#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/count.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/push_back.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<count_if, same_as<int>>();
  test_pack2<count_if, void>();

  using odd = push_back<number<2>, mod<>>;

  ut::same<_5, emp::count_if<seq_0_1_2_3_4_5_6_7_8_9, odd>>();
  ut::same<_1, emp::count<seq_0_1_2, _2>>();

  test_context<count_if<odd>, smp::count_if<odd>, 0>()
    .test<_0>()
    .test<_0, _0, _0, _0>()
    .test<_3, _1, _1, _1>()
    .test<_2, _0, _1, _2, _3>()
    ;

  test_context<count_if<always<na>>, smp::count_if<smp::always<na>>, 0>()
    .test<_0>()
    .not_invocable<_0>()
    ;

  test_context<count<_1>, smp::count<_1>, 0>()
    .test<_0>()
    .test<_0, _0, _0, _0>()
    .test<_3, _1, _1, _1>()
    .test<_1, _0, _1, _3>()
    .test<_2, _0, _1, _3, _1>()
    ;

  ut::not_invocable<smp::count<_1, bad_function>>();
  ut::not_invocable<smp::count<_1, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::count_if<always<void>>, _1>();
  ut::not_invocable<smp::count_if<always<_1>, bad_function>>();
  ut::not_invocable<smp::count_if<always<_1>, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::count_if<bad_function, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
