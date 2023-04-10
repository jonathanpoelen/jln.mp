#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/map/map_erase.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<map_erase, seq_0>();

  ut::same<list<seq_0>, emp::map_erase<list<seq_0, seq_1_0>, _1>>();
  ut::same<list<seq_0, seq_1_0>, emp::map_erase<list<seq_0, seq_1_0>, _2>>();

  test_context<map_erase<_2>, smp::map_erase<_2>>()
    .test<list<>>()
    .test<list<seq_0>, seq_0>()
    .test<list<seq_0>, seq_0, seq_2_0>()
    .test<list<seq_0, seq_1>, seq_0, seq_2_0, seq_1>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  ut::not_invocable<smp::map_erase<_0, bad_function>, seq_0>();
}

TEST_SUITE_END()
