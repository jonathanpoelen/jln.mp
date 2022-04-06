#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/value_type.hpp"

TEST_SUITE_BEGIN()

struct dummy
{
  using value_type = int;
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<value_type>().test_unary();
  test_pack3<value_type>();

  test_context<value_type<>, smp::value_type<>>()
    .test<int, dummy>()
    .not_invocable<>()
    .not_invocable<list<>>()
    .not_invocable<dummy, dummy>()
    ;

  ut::not_invocable<smp::value_type<smp::value_type<>>, dummy>();
  ut::not_invocable<smp::value_type<bad_function>>();
  ut::not_invocable<smp::value_type<bad_function>, int>();
  ut::not_invocable<smp::value_type<bad_function>, dummy>();
}

TEST_SUITE_END()
