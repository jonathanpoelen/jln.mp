#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/value/has_value.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<has_value>()
    .test_unary()
  ;

  test_context<has_value<>, smp::has_value<>>()
    .test<_0, list<>>()
    .test<_1, _0>()
    .not_invocable<>()
    .not_invocable<_0, _1>()
    ;

  ut::not_invocable<smp::has_value<bad_function>, _1>();
}

TEST_SUITE_END()
