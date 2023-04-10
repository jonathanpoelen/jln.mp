#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/front.hpp"
#include "jln/mp/smp/utility/unpack.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<front>();

  ut::same<_0, emp::front<seq_0_1_2>>();

  test_context<front<>, smp::front<>>()
    .test<_0, _0, _1>()
    .not_invocable<>()
    ;

  test_context<unpack<front<>>, smp::unpack<smp::front<>>, 0>()
    .test<_0, seq_0_1>()
    .test<_0, seq_0>()
    .not_invocable<list<>>()
    .not_invocable<>()
    ;

  ut::not_invocable<smp::front<bad_function>>();
  ut::not_invocable<smp::front<bad_function>, _1>();
}

TEST_SUITE_END()
