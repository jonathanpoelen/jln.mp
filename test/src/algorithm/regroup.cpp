#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/regroup.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/utility/stl_traits.hpp"
#include "jln/mp/smp/algorithm/compare_with.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<regroup>();
  test_pack2<regroup_if>();

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

  test_context<regroup_if<>, smp::regroup_if<>>()
    .test<list<>>()
    .test<list<list<int>>, int>()
    .test<list<list<int, int>>, int, int>()
    .test<list<list<int, int, int>>, int, int, int>()
    .test<list<list<int>, list<char>>, int, char>()
    .test<list<list<int>, list<char>, list<short>>, int, char, short>()
    .test<list<list<int, int>, list<char>, list<short, short>, list<float>>,
        int, char, short, int, short, float>()
    ;

  test_context<
    regroup_if<compare_with<traits::extent<>, lift<std::is_same>>>,
    smp::regroup_if<smp::compare_with<smp::traits::extent<>, contract<lift<std::is_same>>>>
  >()
    .test<list<>>()
    .test<list<list<int>>, int>()
    .test<list<list<int, int>>, int, int>()
    .test<list<list<int, int, int>>, int, int, int>()
    .test<list<list<int[1]>, list<char[2]>>, int[1], char[2]>()
    .test<list<list<int[1]>, list<char[2]>, list<short[3]>>, int[1], char[2], short[3]>()
    .test<list<list<int[1], char[1]>, list<char[2]>, list<short[3], char[3]>, list<float[4]>>,
        int[1], char[2], short[3], char[1], char[3], float[4]>()
    ;

  ut::not_invocable<smp::regroup_if<bad_function, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::regroup_if<smp::always<true_>, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::regroup_if_with<smp::always<true_>, bad_function>, _1, _1, _1, _1>();
}

TEST_SUITE_END()
