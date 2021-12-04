#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/sizeof.hpp"
#include "jln/mp/smp/algorithm/mismatch.hpp"
#include "jln/mp/algorithm/iota.hpp"
#include "jln/mp/list/push_back.hpp"

TEST_SUITE_BEGIN()

template<class...>
struct mseq;

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<mismatch>();

  using ne = number<-1>;

  ut::same<mseq<ne, _0>, emp::mismatch<list<>, list<>, equal<>, listify, lift<mseq>>>();
  ut::same<mseq<_0, ne>, emp::mismatch<list<>, seq_0_1, equal<>, listify, lift<mseq>>>();
  ut::same<mseq<_0, _1>, emp::mismatch<seq_0_1, list<>, equal<>, listify, lift<mseq>>>();

  ut::same<mseq<ne, _2>, emp::mismatch<seq_0_1, seq_0_1, equal<>, listify, lift<mseq>>>();
  ut::same<list<_0, _0>, emp::mismatch<seq_0_1, seq_1_2, equal<>, listify, lift<mseq>>>();
  ut::same<list<_0, _0>, emp::mismatch<seq_1_2, seq_0_1, equal<>, listify, lift<mseq>>>();

  ut::same<list<_2, _1>, emp::mismatch<seq_0_1_2, seq_0_1>>();
  ut::same<list<_2, ne>, emp::mismatch<seq_0_1, seq_0_1_2>>();

  test_context<mismatch<>, smp::mismatch<>>()
    .test<list<ne, _0>, list<>, list<>>()
    .test<list<_0, ne>, list<>, seq_0_1>()
    .test<list<_0, _1>, seq_0_1, list<>>()

    .test<list<ne, _2>, seq_0_1, seq_0_1>()
    .test<list<_0, _0>, seq_0_1, seq_1_2>()
    .test<list<_0, _0>, seq_1_2, seq_0_1>()

    .test<list<_2, _1>, seq_0_1_2, seq_0_1>()
    .test<list<_2, ne>, seq_0_1, seq_0_1_2>()

    .test<list<_0, _0>, seq_1_2_3, seq_0_1>()
    .test<list<_0, _0>, seq_0_1, seq_1_2_3>()

    .test<list<_0, _0>, seq_0_1_2, seq_1_2>()
    .test<list<_0, _0>, seq_1_2, seq_0_1_2>()

    .test<list<ne, _8>, emp::iota_c<0, 8>, emp::iota_c<0, 8>>()
    .test<list<_0, _0>, emp::iota_c<1, 8>, emp::iota_c<0, 8>>()
    .test<list<_0, _0>, emp::iota_c<0, 8>, emp::iota_c<1, 8>>()

    .test<list<_7, ne>, emp::iota_c<0, 7>, emp::iota_c<0, 8>>()
    .test<list<_7, _1>, emp::iota_c<0, 8>, emp::iota_c<0, 7>>()
    .test<list<_8, ne>, emp::iota_c<0, 8>, emp::iota_c<0, 9>>()
    .test<list<_8, _1>, emp::iota_c<0, 9>, emp::iota_c<0, 8>>()

    .test<list<ne, _10>, emp::iota_c<0, 10>, emp::iota_c<0, 10>>()
    .test<list<_0, _0>, emp::iota_c<1, 10>, emp::iota_c<0, 10>>()
    .test<list<_0, _0>, emp::iota_c<0, 10>, emp::iota_c<1, 10>>()

    .test<list<_7, _0>,
      emp::iota_c<0, 7, 1, push_back<_100>>,
      emp::iota_c<0, 8>>()
    .test<list<_7, _0>,
      emp::iota_c<0, 8>,
      emp::iota_c<0, 7, 1, push_back<_100>>>()

    .test<list<_9, _0>,
      emp::iota_c<0, 9, 1, push_back<_100>>,
      emp::iota_c<0, 10>>()
    .test<list<_9, _0>,
      emp::iota_c<0, 10>,
      emp::iota_c<0, 9, 1, push_back<_100>>>()

    .not_invocable<>()
    .not_invocable<int>()
    .not_invocable<list<>>()
    .not_invocable<int, int>()
    ;

  test_context<mismatch<equal<>, identity>, smp::mismatch<mp::equal<>, mp::identity>>()
    .not_invocable<list<>, list<>>()
    .not_invocable<list<>, seq_0_1>()
    .not_invocable<seq_0_1, list<>>()
    .not_invocable<seq_0_1_2, seq_1_2>()
    .not_invocable<seq_1_2, seq_0_1_2>()
    .not_invocable<>()
    .not_invocable<int>()
    .not_invocable<list<>>()
    .not_invocable<int, int>()
    ;

  ut::not_invocable<smp::mismatch<smp::always<na>>, seq_1_2, seq_1_2>();
  ut::not_invocable<smp::mismatch<bad_function>, seq_0_1_2, seq_1_2>();
}

TEST_SUITE_END()
