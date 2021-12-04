#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/index.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<index_of, int>();

  ut::same<_2, emp::index_of<seq_0_1_2_3, _2>>();
  ut::same<_4, emp::index_of<seq_0_1_2_3, int>>();

  test_context<index_if<equal_to<_3>>, smp::index_if<smp::equal_to<_3>>>()
    .test<_0>()
    .test<_3, _0, _1, _2, _3>()
    .test<_2, _1, _2, _3>()
    .not_invocable<void, void>()
    .not_invocable<void>()
    ;

  ut::not_invocable<smp::index_of<void, bad_function, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::index_if<smp::always<na>>, _1, _1, _1, _1>();
  ut::not_invocable<smp::index_if<void>, _1, _1, _1, _1>();
  ut::not_invocable<smp::index_if<always<void>>, _1, _1, _1, _1>();
  ut::not_invocable<smp::index_if<always<_1>, bad_function, size<>>, _1, _1, _1, _1>();
  ut::not_invocable<smp::index_if<always<_0>, identity, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::index_if<bad_function>, _1, _1, _1, _1>();
}

TEST_SUITE_END()
