// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
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
  namespace z = optimizer;
  namespace t = optimizer::types;

  test_context<lift<z::optimize>, void>()
    .test<t::uncallable::f<>, value_type<>, t::uncallable>()
    .test<t::uncallable::f<>, value_type<>, z::seq<int, int>>()
    .test<z::optimized_result_t<int, always<int>>, value_type<>, dummy>()
    .test<z::optimized_result_t<t::any, value_type<>>, value_type<>, t::any>()
    ;

  test_unary_pack<value_type>();

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
