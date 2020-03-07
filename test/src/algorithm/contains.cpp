#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/contains.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<contains, void>();

  ut::same<true_, emp::contains<seq_0_1_2, _1>>();

  test_context<contains<_1>, smp::contains<_1>>()
    .test<false_>()
    .test<false_, _0>()
    .test<true_, _1>()
    .test<true_, _1, _1, _1>()
    .test<false_, _0, _0, _0>()
    .test<true_, _0, _0, _1>()
    ;

  ut::not_invocable<smp::contains<void, bad_function>, void>();
}

TEST_SUITE_END()
