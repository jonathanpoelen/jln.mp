#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/set/set_push_back_elements.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<set_push_back_elements>();

  test_context<set_push_back_elements<>, smp::set_push_back_elements<>>()
    .test<seq_1_2, seq_1_2>()
    .test<seq_1_2, seq_1_2, _2>()
    .test<seq_1_2_3, seq_1_2, _3>()
    .test<seq_0_1_2_3, seq_0_1, _2, _3>()
    .not_invocable<>()
    .not_invocable<_1>()
    ;

  ut::not_invocable<smp::set_push_back_elements<bad_function>>();
  ut::not_invocable<smp::set_push_back_elements<bad_function>, seq_0>();
}

TEST_SUITE_END()
