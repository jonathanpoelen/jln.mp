#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/unpack.hpp"
#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<unpack>()
    .test_unary()
    .test_binary()
  ;

  ut::same<_3, emp::unpack<seq_0_0_0, size<>>>();

  test_context<unpack<size<>>, smp::unpack<smp::size<>>>()
    .test<_0, list<>>()
    .test<_1, seq_1>()
    .test<_3, seq_0_0_0>()
    .test<_4, seq_0_0_0, _0>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  ut::not_invocable<smp::unpack<bad_function>>();
  ut::not_invocable<smp::unpack<bad_function>, list<>>();
}

TEST_SUITE_END()
