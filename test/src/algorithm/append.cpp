#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/append.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<remove_adjacent, inc<>>()
    .test_binary()
    .test_unary()
    ;

  test_pack<remove_adjacent, listify>()
    .test_binary()
    .test_unary()
    ;
}

TEST_SUITE_END()
