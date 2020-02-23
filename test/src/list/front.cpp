#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/front.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<_0, emp::front<seq_0_1_2>>();

  test_context<front<>, smp::front<>>()
    .test<_0, _0, _1>()
    .not_invocable<>()
    ;

  ut::not_invocable<smp::front<bad_function>>();
  ut::not_invocable<smp::front<bad_function>, _1>();
}

TEST_SUITE_END()
