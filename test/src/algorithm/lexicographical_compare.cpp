#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/sizeof.hpp"
#include "jln/mp/smp/algorithm/lexicographical_compare.hpp"
#include "jln/mp/algorithm/iota.hpp"
#include "jln/mp/list/push_back.hpp"

TEST_SUITE_BEGIN()

template<class...>
struct mseq;

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<lexicographical_compare>();

  ut::same<_0, emp::lexicographical_compare<list<>, list<>>>();
  ut::same<_1, emp::lexicographical_compare<list<>, seq_0_1>>();
  ut::same<_0, emp::lexicographical_compare<seq_0_1, list<>>>();

  ut::same<_0, emp::lexicographical_compare<seq_0_1, seq_0_1>>();
  ut::same<_1, emp::lexicographical_compare<seq_0_1, seq_1_2>>();
  ut::same<_0, emp::lexicographical_compare<seq_1_2, seq_0_1>>();

  ut::same<_0, emp::lexicographical_compare<seq_0_1_2, seq_0_1>>();
  ut::same<_1, emp::lexicographical_compare<seq_0_1, seq_0_1_2>>();

  ut::same<_0, emp::lexicographical_compare2<seq_0_1_2, seq_0_1>>();
  ut::same<_1, emp::lexicographical_compare2<seq_0_1, seq_0_1_2>>();

  test_context<lexicographical_compare<>, smp::lexicographical_compare<>>()
    .test<_0, list<>, list<>>()
    .test<_1, list<>, seq_0_1>()
    .test<_0, seq_0_1, list<>>()

    .test<_0, seq_0_1, seq_0_1>()
    .test<_1, seq_0_1, seq_1_2>()
    .test<_0, seq_1_2, seq_0_1>()

    .test<_0, seq_0_1_2, seq_0_1>()
    .test<_1, seq_0_1, seq_0_1_2>()

    .test<_0, seq_1_2_3, seq_0_1>()
    .test<_1, seq_0_1, seq_1_2_3>()

    .test<_1, seq_0_1_2, seq_1_2>()
    .test<_0, seq_1_2, seq_0_1_2>()

    .test<_0, emp::iota_c<0, 8>, emp::iota_c<0, 8>>()
    .test<_0, emp::iota_c<1, 8>, emp::iota_c<0, 8>>()
    .test<_1, emp::iota_c<0, 8>, emp::iota_c<1, 8>>()

    .test<_1, emp::iota_c<0, 7>, emp::iota_c<0, 8>>()
    .test<_0, emp::iota_c<0, 8>, emp::iota_c<0, 7>>()
    .test<_1, emp::iota_c<0, 8>, emp::iota_c<0, 9>>()
    .test<_0, emp::iota_c<0, 9>, emp::iota_c<0, 8>>()

    .test<_0, emp::iota_c<0, 10>, emp::iota_c<0, 10>>()
    .test<_0, emp::iota_c<1, 10>, emp::iota_c<0, 10>>()
    .test<_1, emp::iota_c<0, 10>, emp::iota_c<1, 10>>()

    .test<_0,
      emp::iota_c<0, 7, 1, push_back<_100>>,
      emp::iota_c<0, 8>>()
    .test<_1,
      emp::iota_c<0, 8>,
      emp::iota_c<0, 7, 1, push_back<_100>>>()

    .test<_0,
      emp::iota_c<0, 9, 1, push_back<_100>>,
      emp::iota_c<0, 10>>()
    .test<_1,
      emp::iota_c<0, 10>,
      emp::iota_c<0, 9, 1, push_back<_100>>>()

    .not_invocable<>()
    .not_invocable<int>()
    .not_invocable<list<>>()
    .not_invocable<int, int>()
    ;

  test_context<lexicographical_compare2<>, smp::lexicographical_compare2<>>()
    .test<_0, list<>, list<>>()
    .test<_1, list<>, seq_0_1>()
    .test<_0, seq_0_1, list<>>()

    .test<_0, seq_0_1_2, seq_0_1>()
    .test<_1, seq_0_1, seq_0_1_2>()

    .test<_0, emp::iota_c<0, 10>, emp::iota_c<0, 10>>()
    .test<_0, emp::iota_c<1, 10>, emp::iota_c<0, 10>>()
    .test<_1, emp::iota_c<0, 10>, emp::iota_c<1, 10>>()

    .not_invocable<>()
    .not_invocable<int>()
    .not_invocable<list<>>()
    .not_invocable<int, int>()
  ;

  test_context<
    lexicographical_compare<less<>, listify>,
    smp::lexicographical_compare<smp::less<>, smp::listify>
  >()
    .test<list<_0>, list<>, list<>>()
    .test<list<_1>, list<>, seq_0_1>()
    .test<list<_0>, seq_0_1, list<>>()

    .test<list<_0>, seq_0_1, seq_0_1>()
    .test<list<_1>, seq_0_1, seq_1_2>()
    .test<list<_0>, seq_1_2, seq_0_1>()
  ;

  test_context<
    lexicographical_compare2<less<>, equal<>, listify>,
    smp::lexicographical_compare2<smp::less<>, smp::equal<>, smp::listify>
  >()
    .test<list<_0>, list<>, list<>>()
    .test<list<_1>, list<>, seq_0_1>()
    .test<list<_0>, seq_0_1, list<>>()

    .test<list<_0>, seq_0_1, seq_0_1>()
    .test<list<_1>, seq_0_1, seq_1_2>()
    .test<list<_0>, seq_1_2, seq_0_1>()
  ;

  ut::not_invocable<smp::lexicographical_compare<bad_function>, seq_0_1_2, seq_1_2>();
  ut::not_invocable<smp::lexicographical_compare<mp::equal<>, bad_function>, seq_0_1_2, seq_1_2>();

  ut::not_invocable<smp::lexicographical_compare2<mp::less<>, mp::equal<>, bad_function>, seq_0_1, seq_1_2>();
  ut::not_invocable<smp::lexicographical_compare2<mp::less<>, bad_function>, seq_0_1, seq_1_2>();
  ut::not_invocable<smp::lexicographical_compare2<bad_function>, seq_0_1, seq_1_2>();
}

TEST_SUITE_END()
