#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/set/set_union.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<set_union>();

  test_context<set_union<>, smp::set_union<>>()
    .test<seq_1_2, seq_1_2>()
    .test<seq_1, list<>, seq_1>()
    .test<seq_1_2, list<>, seq_1, seq_2>()
    .test<seq_1_2, seq_1_2, seq_1>()
    .test<seq_1_2, seq_1_2, seq_1_2>()
    .test<seq_1_2, seq_1_2, seq_1, seq_2>()
    .test<seq_1_2, seq_1, seq_1_1_1, seq_2_2>()
    .test<seq_1_2_3, seq_1_2, seq_1_2_3>()
    .test<seq_1_2_3, seq_1_2_3, seq_1, seq_2>()
    .test<list<_3, _0, _1, _2, _4, _6, _8, _10>, seq_3_0, seq_1_2_3, seq_2_4_6_8_10>()
    .not_invocable<>()
    .not_invocable<_1>()
    .not_invocable<seq_1, _1>()
    ;

  ut::not_invocable<smp::set_union<bad_function>>();
  ut::not_invocable<smp::set_union<bad_function>, seq_0>();
}

TEST_SUITE_END()
