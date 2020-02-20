#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/iota.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<seq_0_1_2, emp::iota_c<0, 3>>();
  ut::same<seq_1_3_5, emp::iota_c<1, 3, 2>>();

  ut::same<seq_0_1_2, emp::iota_v_c<0, 3>>();
  ut::same<seq_1_3_5, emp::iota_v_c<1, 3, 2>>();

  test_pack2<iota>();

  test_context<iota<>, smp::iota<>>()
    .test<list<>, _0, _0>()
    .test<list<>, _3, _0>()
    .test<seq_0_1_2, _0, _3>()
    .test<seq_0_0_0, _0, _3, _0>()
    .test<seq_1_1_1, _1, _3, _0>()
    .test<seq_1_2_3, _1, _3>()
    .test<seq_0_2_4, _0, _3, _2>()
    .test<seq_1_3_5, _1, _3, _2>()
    .not_invocable<_1>()
    .not_invocable<_1, _1, _1, _1>()
    ;
}

TEST_SUITE_END()
