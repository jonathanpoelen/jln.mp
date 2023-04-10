#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/map/is_map.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<is_map>();

  ut::same<_1, emp::is_map<list<seq_0_1, seq_1_1>>>();
  ut::same<_0, emp::is_map<list<seq_0_1, seq_0_1>>>();
  ut::same<_0, emp::is_map<list<list<>>>>();
  ut::same<_1, emp::is_map<list<>>>();

  test_context<is_map<>, smp::is_map<>>()
    .test<_1>()
    .test<_0, _0>()
    .test<_0, list<>>()
    .test<_1, seq_0>()
    .test<_1, seq_0_1>()
    .test<_0, seq_0, seq_0>()
    .test<_0, seq_0_1, seq_0>()
    .test<_0, seq_0_1, seq_0_1>()
    .test<_1, seq_0, seq_1>()
    .test<_1, seq_0_1, seq_1_2, seq_2_3>()
    .test<_0, seq_0_1, seq_1_2, seq_0_2>()
    ;

  ut::not_invocable<smp::is_map<bad_function>>();
}

TEST_SUITE_END()
