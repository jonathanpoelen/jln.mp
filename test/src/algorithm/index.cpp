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

  test_pack<index_of, int>()
    .test_unary()
  ;

  ut::same<_2, emp::index_of<seq_0_1_2_3, _2>>();
  ut::same<na, emp::index_of<seq_0_1_2_3, _6>>();

  test_context<
    index_if<equal_than<_3>>,
    smp::index_if<smp::equal_than<_3>>
  >()
    .test<_3, _0, _1, _2, _3>()
    .test<_2, _1, _2, _3>()
    .not_invocable<void, void>()
    .not_invocable<void>()
    .not_invocable<>()
    ;
}

TEST_SUITE_END()
