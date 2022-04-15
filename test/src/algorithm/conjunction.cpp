#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/conjunction.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<_1, emp::conjunction<seq_1_1>>();
  ut::same<_0, emp::conjunction<seq_1_0>>();

  test_unary_pack<conjunction>();

  test_context<conjunction<>, smp::conjunction<>>()
    .test<_1>()
    .test<_1, _1>()
    .test<_1, _1, _1>()
    .test<_0, _0, _1, _1, _1, _1>()
    .test<_0, _1, _0, list<>, _1>()
    .test<_1, _2>()
    .not_invocable<list<>>()
    .not_invocable<_1, _1, list<>>()
    ;

  ut::not_invocable<smp::conjunction<smp::always<na>>>();
  ut::not_invocable<smp::conjunction<bad_function>>();
}

TEST_SUITE_END()
