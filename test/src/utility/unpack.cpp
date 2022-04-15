#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/unpack.hpp"
#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<unpack>();
  test_mulary_pack<unpack_append>();

  ut::same<_3, emp::unpack<seq_0_0_0, size<>>>();
  ut::same<_3, emp::unpack_append<seq_0_0_0, size<>>>();

  test_context<unpack<size<>>, smp::unpack<smp::size<>>>()
    .test<_0, list<>>()
    .test<_1, seq_1>()
    .test<_3, seq_0_0_0>()
    .test<_4, seq_0_0_0, _0>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  test_context<unpack_append<size<>>, smp::unpack_append<smp::size<>>>()
    .test<_0, list<>>()
    .test<_1, seq_1>()
    .test<_3, seq_0_0_0>()
    .test<_4, seq_0_0_0, _0>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  test_context<unpack<listify>, smp::unpack<smp::listify>>()
    .test<list<_3, _0, _1, _2>, seq_0_1_2, _3>()
    ;

  test_context<unpack_append<listify>, smp::unpack_append<smp::listify>>()
    .test<seq_0_1_2_3, seq_0_1_2, _3>()
    ;

  test_context<unpack<identity>, smp::unpack<smp::identity>>()
    .test<_0, seq_0>()
    .not_invocable<seq_0_1>()
    ;

  test_context<unpack_append<identity>, smp::unpack_append<smp::identity>>()
    .test<_0, seq_0>()
    .not_invocable<seq_0_1>()
    ;

  ut::not_invocable<smp::unpack<bad_function>>();
  ut::not_invocable<smp::unpack<bad_function>, list<>>();
  ut::not_invocable<smp::unpack_append<bad_function>>();
  ut::not_invocable<smp::unpack_append<bad_function>, list<>>();
}

TEST_SUITE_END()
