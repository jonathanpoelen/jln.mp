#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/is.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<is, _1>();

  test_context<is<_1>, smp::is<_1>>()
    .test<_0, list<>>()
    .test<_1, _1>()
    .not_invocable<>()
    .not_invocable<_0, _1>()
    ;

  ut::not_invocable<smp::is<int, bad_function>>();
  ut::not_invocable<smp::is<int, bad_function>, int>();
}

TEST_SUITE_END()
