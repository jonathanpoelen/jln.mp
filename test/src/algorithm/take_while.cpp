#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/take_while.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/utility/same_as.hpp"

TEST_SUITE_BEGIN()

template<template<class...> class List, template<class...> class List2>
void test_take_while()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using Smp = smp::take_while<
    smp::equal_than<_2>,
    detail::sfinae<cfe<List>>, detail::sfinae<cfe<List2>>
  >;

  test_context<take_while<equal_than<_2>, cfe<List>, cfe<List2>>, Smp, 0>()
    .template test<List2<>>()
    .template test<List2<_0>, _0>()
    .template test<List2<_0, _1>, _0, _1>()
    .template test<List<_0, _1>, _0, _1, _2>()
    .template test<List<_0, _1>, _0, _1, _2, _3>()
    .template not_invocable<_0, _1, bad_number>()
    .template not_invocable<bad_number>()
    ;

  test_context<Smp, void>()
    .template test<List<_0, _1>, _0, _1, _2, bad_number>()
    ;
}

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<take_while>();

  ut::same<seq_0_1, emp::take_while<list<_0, _1, _2, _3>, same_as<_2>>>();
  ut::same<ut::other_list<_0, _1>, emp::take_while<list<_0, _1>, same_as<_2>, listify, ut::other_listify>>();

  test_take_while<list, list>();
  test_take_while<list, ut::other_list>();

  ut::not_invocable<smp::take_while<bad_function>, _1, _1>();
  ut::not_invocable<smp::take_while<bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::take_while<bad_function, bad_function, bad_function>, _1, _1>();
}

TEST_SUITE_END()
