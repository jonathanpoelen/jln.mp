#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/prefix.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<prefix, int>();

  ut::same<list<>, emp::prefix<list<>, int>>();
  ut::same<list<int, _0>, emp::prefix<seq_0, int>>();

  test_context<prefix<int>, smp::prefix<int>>()
    .test<list<>>()
    .test<list<int, _0>, _0>()
    .test<list<int, _0, int, _1>, _0, _1>()
    .test<list<int, _0, int, _1, int, _2>, _0, _1, _2>()
    ;

  ut::not_invocable<smp::prefix<void, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
