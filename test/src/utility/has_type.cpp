#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/has_type.hpp"

TEST_SUITE_BEGIN()

struct dummy
{
  using type = int;
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<has_type>()
    .test_unary()
  ;

  test_context<has_type<>, smp::has_type<>>()
    .test<_0, list<>>()
    .test<_1, dummy>()
    .not_invocable<>()
    .not_invocable<_0, _1>()
    ;
}

TEST_SUITE_END()
