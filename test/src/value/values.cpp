#include "test.hpp"
#include "test/numbers.hpp"
#include "test/values.hpp"

#include "jln/mp/smp/value/values.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<values>()
    .test_binary()
    .test_unary()
  ;

  test_context<values<>, smp::values<>>()
    .test<list<>>()
    .test<vseq_0, _0>()
    .test<vseq_0_1_2, _0, _1, _2>()
    .test<vseq_0_1_2, _0, v1, _2>()
    .not_invocable<bad_val>()
    ;

  ut::not_invocable<smp::values<bad_function>>();
  ut::not_invocable<smp::values<bad_function>, _1>();
}

TEST_SUITE_END()
