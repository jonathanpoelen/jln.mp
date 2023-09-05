// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;
  namespace z = optimizer;
  namespace t = optimizer::types;

  test_context<lift<z::optimize>, void>()
    .test<t::uncallable::f<>, size<>, t::uncallable>()
    .test<z::optimized_result_t<_1, always<_1>>, size<>, int>()
    .test<z::optimized_result_t<_2, always<_2>>, size<>, z::seq<int, int>>()
    .test<z::optimized_result_t<z::union_<t::uncallable, _1>, always<_1>>,
      size<>, z::union_<t::uncallable, int>>()
    .test<z::optimized_result_t<_2, always<_2>>,
      size<>, z::union_<z::seq<int, int>, z::seq<void, void>>>()
    .test<z::optimized_result_t<t::number, size<>>, size<>, z::pack<int>>()
    ;

  test_unary_pack<size>();

  ut::same<_3, emp::size<list<int, int, int>>>();

  test_context<size<>, smp::size<>>()
    .test<_0>()
    .test<_1, int>()
    .test<_2, int, void>()
    .test<_3, int, void, char>()
    ;

  ut::same<smp::size<>, contract<mp::size<>>>();

  ut::not_invocable<smp::size<bad_function>>();
}

TEST_SUITE_END()
