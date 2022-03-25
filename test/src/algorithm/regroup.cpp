#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/regroup.hpp"
#include "jln/mp/smp/utility/always.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<regroup>();

  ut::same<list<list<int, int>, list<char>, list<short, short>>,
    emp::regroup<list<int, char, int, short, short>>>();

  test_context<regroup<>, smp::regroup<>>()
    .test<list<>>()
    .test<list<list<int>>, int>()
    .test<list<list<int, int>>, int, int>()
    .test<list<list<int, int, int>>, int, int, int>()
    .test<list<list<int>, list<char>>, int, char>()
    .test<list<list<int>, list<char>, list<short>>, int, char, short>()
    .test<list<list<int, int>, list<char>, list<short, short>, list<float>>,
        int, char, short, int, short, float>()
    ;

  ut::not_invocable<smp::regroup<smp::always<na>>, _1, _1, _1, _1>();
  ut::not_invocable<smp::regroup<bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::regroup_with<bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::regroup_with<lift_t<list>>, _1, _1, _1, _1>();
  ut::not_invocable<smp::regroup_with<listify, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::regroup_with<bad_function, bad_function>, _1, _1, _1, _1>();
}

TEST_SUITE_END()
