#include "test.hpp"
#include "test/values.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/value/as_val.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace TU::ints;

  test_pack<as_val>()
    .test_unary()
  ;

  test_context<as_val<>, smp::as_val<>>()
    // .test<v1, _1>()
    .test<v1, v1>()
    .not_invocable<>()
    .not_invocable<list<>>()
    .not_invocable<_0, _1>()
    ;
}

TEST_SUITE_END()
