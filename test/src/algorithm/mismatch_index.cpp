#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/sizeof.hpp"
#include "jln/mp/smp/algorithm/mismatch_index.hpp"
#include "jln/mp/algorithm/iota.hpp"
#include "jln/mp/list/push_back.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_binary_pack<mismatch_index>();
  test_unary_pack<mismatch_index, listify>();

  ut::same<_0, emp::mismatch_index<list<>, list<>>>();
  ut::same<_0, emp::mismatch_index<list<>, seq_0_1>>();
  ut::same<_0, emp::mismatch_index<seq_0_1, list<>>>();

  ut::same<_2, emp::mismatch_index<seq_0_1, seq_0_1>>();
  ut::same<_0, emp::mismatch_index<seq_0_1, seq_1_2>>();
  ut::same<_0, emp::mismatch_index<seq_1_2, seq_0_1>>();

  ut::same<_2, emp::mismatch_index<seq_0_1_2, seq_0_1>>();
  ut::same<_2, emp::mismatch_index<seq_0_1, seq_0_1_2>>();

  test_context<mismatch_index<>, smp::mismatch_index<>>()
    .test<_0, list<>, list<>>()
    .test<_0, list<>, seq_0_1>()
    .test<_0, seq_0_1, list<>>()

    .test<_2, seq_0_1, seq_0_1>()
    .test<_0, seq_0_1, seq_1_2>()
    .test<_0, seq_1_2, seq_0_1>()

    .test<_2, seq_0_1_2, seq_0_1>()
    .test<_2, seq_0_1, seq_0_1_2>()

    .test<_0, seq_1_2_3, seq_0_1>()
    .test<_0, seq_0_1, seq_1_2_3>()

    .test<_0, seq_0_1_2, seq_1_2>()
    .test<_0, seq_1_2, seq_0_1_2>()

    .test<_8, emp::iota_c<0, 8>, emp::iota_c<0, 8>>()
    .test<_0, emp::iota_c<1, 8>, emp::iota_c<0, 8>>()
    .test<_0, emp::iota_c<0, 8>, emp::iota_c<1, 8>>()

    .test<_7, emp::iota_c<0, 7>, emp::iota_c<0, 8>>()
    .test<_7, emp::iota_c<0, 8>, emp::iota_c<0, 7>>()
    .test<_8, emp::iota_c<0, 8>, emp::iota_c<0, 9>>()
    .test<_8, emp::iota_c<0, 9>, emp::iota_c<0, 8>>()

    .test<_10, emp::iota_c<0, 10>, emp::iota_c<0, 10>>()
    .test<_0, emp::iota_c<1, 10>, emp::iota_c<0, 10>>()
    .test<_0, emp::iota_c<0, 10>, emp::iota_c<1, 10>>()

    .test<_7,
      emp::iota_c<0, 7, 1, push_back<_100>>,
      emp::iota_c<0, 8>>()
    .test<_7,
      emp::iota_c<0, 8>,
      emp::iota_c<0, 7, 1, push_back<_100>>>()

    .test<_9,
      emp::iota_c<0, 9, 1, push_back<_100>>,
      emp::iota_c<0, 10>>()
    .test<_9,
      emp::iota_c<0, 10>,
      emp::iota_c<0, 9, 1, push_back<_100>>>()

    .not_invocable<>()
    .not_invocable<int>()
    .not_invocable<list<>>()
    .not_invocable<int, int>()
    ;

  test_context<mismatch_index<identity>, smp::mismatch_index<mp::identity>>()
    .test<_0, list<>, list<>>()
    .test<_0, list<>, seq_0_1>()
    .test<_0, seq_0_1, list<>>()
    .not_invocable<seq_0_1_2, seq_1_2>()
    .not_invocable<seq_1_2, seq_0_1_2>()
    .not_invocable<>()
    .not_invocable<int>()
    .not_invocable<list<>>()
    .not_invocable<int, int>()
    ;

  ut::not_invocable<smp::mismatch_index<smp::always<na>>, seq_1_2, seq_1_2>();
  ut::not_invocable<smp::mismatch_index<bad_function>, seq_0_1_2, seq_1_2>();
}

TEST_SUITE_END()
