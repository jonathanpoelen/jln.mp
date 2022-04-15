#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/remove_unique.hpp"
#include "jln/mp/smp/functional/each.hpp"
#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/utility/unpack.hpp"
#include "jln/mp/smp/list/at.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<remove_unique>();
  test_mulary_pack<remove_unique_if, size<>>();

  ut::same<emp::numbers<0, 0, 2, 2>, emp::remove_unique<emp::numbers<0, 1, 0, 2, 2, 3>>>();

  test_context<remove_unique<>, smp::remove_unique<>>()
    .test<list<>>()
    .test<list<>, _0>()
    .test<seq_0_0, _0, _0>()
    .test<list<>, _0, _1>()
    .test<list<>, _0, _1, _2>()
    .test<list<_0, _0, _0, _0, _0>, _0, _0, _0, _0, _0>()
    .test<list<_0, _0, _0, _2, _2, _2, _0, _0>,
      _0, _0, _1, _0, _2, _2, _2, _0, _0, _3>()
    .test<list<int&, int&>,
      int, int&, int&&, int const, int const&, int const&&, int&>()
    ;

  test_context<remove_unique_if<>, smp::remove_unique_if<>>()
    .test<list<>>()
    .test<list<>, _0>()
    .test<seq_0_0, _0, _0>()
    .test<list<>, _0, _1>()
    .test<list<>, _0, _1, _2>()
    .test<list<_0, _0, _0, _0, _0>, _0, _0, _0, _0, _0>()
    .test<list<_0, _0, _0, _2, _2, _2, _0, _0>,
      _0, _0, _1, _0, _2, _2, _2, _0, _0, _3>()
    .test<list<int&, int&>,
      int, int&, int&&, int const, int const&, int const&&, int&>()
    ;

  using first = unpack<at0<>>;
  using smp_first = smp::unpack<smp::at0<>>;
  test_context<
    remove_unique_if<each<first, first, lift<std::is_same>>>,
    smp::remove_unique_if<smp::each<smp_first, smp_first, smp::lift<std::is_same>>>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<seq_0_0, seq_0_1>, seq_0_0, seq_0_1>()
    .test<list<seq_0_0, seq_0_1>, seq_0_0, seq_0_1, seq_1_0>()
    .test<list<seq_0_0, seq_0_1, seq_2_0, seq_0_2, seq_2_0>,
      seq_0_0, seq_0_1, seq_1_0, seq_2_0, seq_0_2, seq_2_0>()
    .not_invocable<_0, _0>()
    ;

  ut::not_invocable<smp::remove_unique<bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::remove_unique_if<smp::always<na>>, _1, _1, _1, _1>();
  ut::not_invocable<smp::remove_unique_if<always<void>>, _1, _1, _1, _1>();
  ut::not_invocable<smp::remove_unique_if<bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::remove_unique_if<lift<std::is_same>, bad_function>, _1, _1, _1, _1>();
}

TEST_SUITE_END()
