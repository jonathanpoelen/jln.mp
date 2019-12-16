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

  test_context<
    index_for<always<_3>>,
    smp::index_for<smp::always<_3>>
  >()
    .test<number<-3>>()
    .test<number<-2>, void>()
    .test<number<-1>, void, void>()
    .test<_0, void, void, void>()
    .test<_1, void, void, void, void>()
    ;

  test_context<
    index_for<always<bad_number>>,
    smp::index_for<smp::always<bad_number>>
  >()
    .not_invocable<>()
    .not_invocable<void>()
    ;

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
