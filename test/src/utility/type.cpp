#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/type.hpp"

TEST_SUITE_BEGIN()

struct dummy
{
  using type = int;
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<type_>().test_unary();
  test_pack3<type_>();

  test_context<type_<>, smp::type_<>>()
    .test<int, dummy>()
    .not_invocable<>()
    .not_invocable<list<>>()
    .not_invocable<dummy, dummy>()
    ;

  ut::not_invocable<smp::type_<bad_function>>();
  ut::not_invocable<smp::type_<bad_function>, int>();
  ut::not_invocable<smp::type_<bad_function>, dummy>();
}

TEST_SUITE_END()
