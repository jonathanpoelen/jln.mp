#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/same_as.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace TU::ints;

  test_pack<same_as>()
    .test_unary()
    .test_binary()
  ;

  test_context<same_as<_1>, smp::same_as<_1>>()
    .test<_0, list<>>()
    .test<_1, _1>()
    .not_invocable<>()
    .not_invocable<_0, _1>()
    ;
}

TEST_SUITE_END()
