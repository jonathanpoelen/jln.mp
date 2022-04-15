#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/suffix.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<suffix, int>();

  ut::same<list<>, emp::suffix<list<>, int>>();
  ut::same<list<_0, int>, emp::suffix<seq_0, int>>();

  test_context<suffix<int>, smp::suffix<int>>()
    .test<list<>>()
    .test<list<_0, int>, _0>()
    .test<list<_0, int, _1, int>, _0, _1>()
    .test<list<_0, int, _1, int, _2, int>, _0, _1, _2>()
    ;

  ut::not_invocable<smp::suffix<void, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
