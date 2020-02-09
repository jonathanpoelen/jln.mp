#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/unique.hpp"
#include "jln/mp/smp/functional/fork.hpp"
#include "jln/mp/smp/list/at.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<unique>()
    .test_variadic()
    .test_binary()
    .test_unary()
    ;

  ut::same<seq_0_1_2, emp::unique<emp::numbers<0, 1, 0, 2, 2>>>();

  test_context<unique<>, smp::unique<>, 0>()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<seq_0, _0, _0>()
    .test<seq_0_1, _0, _1>()
    .test<seq_0_1_2, _0, _1, _2>()
    .test<seq_0, _0, _0, _0, _0, _0>()
    .test<seq_0_1_2_3, _0, _0, _1, _0, _2, _2, _2, _0, _0, _3>()
    ;

  using first = unpack<at0<>>;
  using smp_first = smp::unpack<smp::at0<>>;
  // TODO each<first, first, cfe<std::is_same>>
  test_context<
    unique_if<fork<at0<first>, at1<first>, cfe<std::is_same>>>,
    smp::unique_if<smp::fork<smp::at0<smp_first>, smp::at1<smp_first>, smp::cfe<std::is_same>>>
  >()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<list<list<_0, _0>>, list<_0, _0>, list<_0, _1>>()
    .test<list<list<_0, _0>, list<_1, _0>>, list<_0, _0>, list<_0, _1>, list<_1, _0>>()
    .not_invocable<_0, _0>()
    ;
}

TEST_SUITE_END()
