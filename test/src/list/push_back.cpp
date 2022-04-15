#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/push_back.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<push_back, void>();

  test_context<push_back<_2>, smp::push_back<_2>>()
    .test<seq_2>()
    .test<seq_1_2, _1>()
    .test<seq_0_1_2, _0, _1>()
    ;

  ut::not_invocable<smp::push_back<_1, bad_function>>();
}

TEST_SUITE_END()
