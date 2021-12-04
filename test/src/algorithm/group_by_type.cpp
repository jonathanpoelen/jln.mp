#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/group_by_type.hpp"
#include "jln/mp/smp/utility/always.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<group_by_type>();

  ut::same<list<list<int, int>, list<char>, list<short, short>>,
    emp::group_by_type<list<int, char, int, short, short>>>();

  test_context<group_by_type<>, smp::group_by_type<>>()
    .test<list<>>()
    .test<list<list<int>>, int>()
    .test<list<list<int, int>>, int, int>()
    .test<list<list<int, int, int>>, int, int, int>()
    .test<list<list<int>, list<char>>, int, char>()
    .test<list<list<int>, list<char>, list<short>>, int, char, short>()
    .test<list<list<int, int>, list<char>, list<short, short>, list<float>>,
        int, char, short, int, short, float>()
    ;

  ut::not_invocable<smp::group_by_type<smp::always<na>>, _1, _1, _1, _1>();
  ut::not_invocable<smp::group_by_type<bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::group_by_type_with<bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::group_by_type_with<lift_t<list>>, _1, _1, _1, _1>();
  ut::not_invocable<smp::group_by_type_with<listify, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::group_by_type_with<bad_function, bad_function>, _1, _1, _1, _1>();
}

TEST_SUITE_END()
