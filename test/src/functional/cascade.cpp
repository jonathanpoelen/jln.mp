#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/cascade.hpp"
#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

template<class...> class list1 {};
template<class...> class list2 {};
template<class...> class list3 {};

template<template<class...> class F>
using make_cascade = F<
  jln::mp::lift<list1>,
  jln::mp::lift<list2>,
  jln::mp::lift<list3>
>;

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<cascade>();
  test_mulary_pack<cascade, listify>();
  test_mulary_pack<cascade, listify, listify>();
  test_mulary_pack<cascade, listify, listify, listify>();

  test_context<make_cascade<cascade>, make_cascade<smp::cascade>>()
    .test<list3<>>()
    .test<list3<list2<>>, list<>>()
    .test<list3<list2<list1<>>>, list<list<>>>()
    .test<list3<list2<list1<_1, _2>>>, list<list<_1, _2>>>()
    .test<list3<list2<list1<>, list1<_0>>, list2<list1<_1, _2>>>,
      list<list<>, list<_0>>, list<list<_1, _2>>>()
    .not_invocable<int>()
    .not_invocable<list<int>>()
    ;

  ut::not_invocable<smp::cascade<smp::always<na>>, list<list<>>>();
  ut::not_invocable<smp::cascade<bad_function>, list<list<>>>();
}

TEST_SUITE_END()
