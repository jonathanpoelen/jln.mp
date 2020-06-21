#include "test.hpp"

#include "jln/mp/smp/utility/sizeof.hpp"
#include "jln/mp/smp/algorithm/compare_with.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  test_pack2<compare_with>();

  ut::same<false_, emp::compare_with<sizeof_<>, int, int>>();
  ut::same<true_, emp::compare_with<sizeof_<>, char[1], char[2]>>();
  ut::same<false_, emp::compare_with<sizeof_<>, char[2], char[1]>>();

  test_context<compare_with<mp::sizeof_<>>, smp::compare_with<smp::sizeof_<>>>()
    .test<true_, char[1], char[2]>()
    .test<false_, char[2], char[1]>()
    .not_invocable<>()
    .not_invocable<int>()
    .not_invocable<int, int, int>()
    ;

  ut::not_invocable<smp::compare_with<bad_function>, int, int>();
  ut::not_invocable<smp::compare_with<smp::sizeof_<>, bad_function>, int, int>();
}

TEST_SUITE_END()
