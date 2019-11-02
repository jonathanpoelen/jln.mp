#include "test.hpp"
#include "test/values.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/value/is_val.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace TU::ints;

  test_pack<is_val>()
    .test_unary()
  ;

  test_context<is_val<>, smp::is_val<>>()
    .test<_0, list<>>()
    .test<_0, _0>()
    .test<_1, v0>()
    .not_invocable<>()
    .not_invocable<v0, v1>()
    .not_invocable<_0, _1>()
    ;
}

TEST_SUITE_END()
