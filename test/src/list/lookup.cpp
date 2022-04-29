#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/lookup.hpp"
#include "jln/mp/algorithm/make_int_sequence.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<precomputed_indexes_at, _0>();
  test_unary_pack<build_indexed>();
  test_unary_pack<lookup>();

  using l = list<int, char, void, float>;

  ut::same<void, emp::lookup<l, _2>>();

  using precomputed_indexes = emp::build_indexed<l>;
  ut::same<void, emp::precomputed_indexes_at_c<precomputed_indexes, 2>>();

  test_context<lookup<l>, smp::lookup<l>>()
    .test<int, _0>()
    .test<char, _1>()
    .test<void, _2>()
    .test<float, _3>()
    .not_invocable<>()
    .not_invocable<_4>()
    ;

  test_context<precomputed_indexes_at_c<2>, smp::precomputed_indexes_at_c<2>>()
    .test<void, precomputed_indexes>()
    .not_invocable<>()
    .not_invocable<list<>>()
    .not_invocable<listify>()
    ;

  ut::not_invocable<smp::lookup<_0>, _0>();
  ut::not_invocable<smp::lookup<l, smp::always<na>>, _0>();
  ut::not_invocable<smp::lookup<l, bad_function>, _0>();
  // ut::not_invocable<smp::lookup<emp::make_int_sequence_c<4097>>, number<4097>>();
}

TEST_SUITE_END()
