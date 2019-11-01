#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/unpack.hpp"
#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace TU::ints;

  test_pack<unpack>()
    .test_unary()
    .test_binary()
  ;

  test_context<unpack<size<>>, smp::unpack<smp::size<>>>()
    .test<_0, list<>>()
    .test<_1, seq_1>()
    .test<_3, seq_0_0_0>()
    .test<_4, seq_0_0_0, _0>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;
}

TEST_SUITE_END()
