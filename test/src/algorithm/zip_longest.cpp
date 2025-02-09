// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/zip_longest.hpp"
#include "jln/mp/smp/algorithm/matrix_shortest.hpp"
#include "jln/mp/smp/functional/continuation.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

template<class...>
struct another_list;

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<
    list<
      emp::numbers<40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 410, 411, 412, 413, 414, 415, 416, 417, 418>,
      emp::numbers<30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 310, 311, 312, 313, 314, 315, 316, 317, 318>,
      emp::numbers<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 9999>
    >,
    emp::zip_longest<list<
      emp::numbers<40,  30, 0>, emp::numbers<41,  31, 1>,
      emp::numbers<42,  32, 2>, emp::numbers<43,  33, 3>,
      emp::numbers<44,  34, 4>, emp::numbers<45,  35, 5>,
      emp::numbers<46,  36, 6>, emp::numbers<47,  37, 7>,
      emp::numbers<48,  38, 8>, emp::numbers<49,  39, 9>,
      emp::numbers<410, 310, 10>, emp::numbers<411, 311, 11>,
      emp::numbers<412, 312, 12>, emp::numbers<413, 313, 13>,
      emp::numbers<414, 314, 14>, emp::numbers<415, 315, 15>,
      emp::numbers<416, 316, 16>, emp::numbers<417, 317, 17>,
      emp::numbers<418, 318>
    >, number<9999>>
  >();

  test_mulary_pack<zip_longest_with, void>();
  test_mulary_pack<zip_longest_with, void, listify>();

  test_context<zip_longest<void>, smp::zip_longest<void>>()
    .test<list<>, list<>, list<>>()
    .test<list<list<_0>>, list<_0>>()
    .test<list<list<_0>, list<_1>>, list<_0, _1>>()
    .test<list<list<_0, _1>>, list<_0>, list<_1>>()
    .test<list<list<_0, _2>, list<_1, _3>>,
      list<_0, _1>, list<_2, _3>>()
    .test<list<list<_0, _2, _4>, list<_1, _3, _5>>,
      list<_0, _1>, list<_2, _3>, list<_4, _5>>()
    .test<list<list<void, _0>>, list<>, list<_0>>()
    .test<list<list<_0, _1>, list<void, _2>>, list<_0>, list<_1, _2>>()
    .test<list<list<_0, _2, _4>, list<_1, _3, void>>,
      list<_0, _1>, list<_2, _3>, list<_4>>()
    .not_invocable<int>()
    .not_invocable<another_list<>>()
    ;

  test_context<zip_longest_with<void, add<>>, smp::zip_longest_with<void, smp::add<>>>()
    .test<list<>>()
    .test<list<_6, _2>, list<_4, _1>, list<_2, _1>>()
    .not_invocable<list<bad_number>, list<_1>>()
    ;

  test_context<zip_longest_with<_8, add<>>, smp::zip_longest_with<_8, smp::add<>>>()
    .test<list<_6, _9>, list<_4>, list<_2, _1>>()
    ;

  ut::not_invocable<smp::zip_longest<void, smp::always<na>>, seq_0_0, seq_0_0>();
  ut::not_invocable<smp::zip_longest<void, bad_function>>();
  ut::not_invocable<smp::zip_longest<void, bad_function>, list<>>();
  ut::not_invocable<smp::zip_longest<void, bad_function>,
    list<>, list<>, list<>, list<>, list<>, list<>, list<>, list<>, list<>>();
  ut::not_invocable<smp::zip_longest_with<void, smp::always<na>>, seq_0_0, seq_0_0>();
  ut::not_invocable<smp::zip_longest_with<void, always<_1>, bad_function>>();
  ut::not_invocable<smp::zip_longest_with<void, always<_1>, bad_function>, list<>>();
  ut::not_invocable<smp::zip_longest_with<void, always<_1>, bad_function>,
    list<>, list<>, list<>, list<>, list<>, list<>, list<>, list<>, list<>>();
  ut::not_invocable<smp::zip_longest_with<void, bad_function, bad_function>>();
  ut::not_invocable<smp::zip_longest_with<void, bad_function, bad_function>, list<>>();
  ut::not_invocable<smp::zip_longest_with<void, bad_function, bad_function>,
    list<>, list<>, list<>, list<>, list<>, list<>, list<>, list<>, list<>>();
}

TEST_SUITE_END()
