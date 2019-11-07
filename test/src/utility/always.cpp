#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<always>()
    .test_unary()
    .test_binary()
  ;

  test_context<always<_1>, smp::always<_1>>()
    .test<_1>()
    .test<_1, list<>>()
    .test<_1, seq_0_0_0>()
    ;

  test_context<always<_1, equal<>>, smp::always<_1, smp::equal<>>>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;
}

TEST_SUITE_END()
