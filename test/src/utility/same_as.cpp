#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/same_as.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<same_as>();

  test_context<same_as<_1>, smp::same_as<_1>>()
    .test<_0, list<>>()
    .test<_1, _1>()
    .not_invocable<>()
    .not_invocable<_0, _1>()
    ;

  ut::not_invocable<smp::same_as<int, bad_function>>();
  ut::not_invocable<smp::same_as<int, bad_function>, int>();
}

TEST_SUITE_END()
