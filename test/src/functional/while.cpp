// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/while.hpp"
#include "jln/mp/smp/functional/continuation.hpp"
#include "jln/mp/smp/functional/if.hpp"
#include "jln/mp/smp/list/push_back.hpp"
#include "jln/mp/smp/list/is_size_of.hpp"
#include "jln/mp/smp/utility/is_not.hpp"
#include "jln/mp/smp/utility/stl_traits.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<while_, ut::unary>();
  test_mulary_pack<while_, ut::binary>();
  test_mulary_pack<while_, ut::listify>();
  test_mulary_pack<while_, is<void>, is<void>>();

  test_context<
    while_<is_not<int****>, traits::add_pointer<>>,
    smp::while_<smp::is_not<int****>, smp::traits::add_pointer<>>
  >()
    .test<int****, int>()
    .not_invocable<>()
    .not_invocable<int, int>()
  ;

  test_context<
    while_xs<is_size_of_c<5, not_<>>, push_back<int, next_recursion>>,
    smp::while_xs<smp::is_size_of_c<5, smp::not_<>>, smp::push_back<int, smp::next_recursion>>
  >()
    .test<list<_1, int, int, int, int>, _1>()
    .test<list<_1, _2, _3, _4, _5>, _1, _2, _3, _4, _5>()
  ;

  ut::not_invocable<smp::while_<smp::always<na>, smp::next_recursion>, _1, _1>();
  ut::not_invocable<smp::while_<smp::always<_0>, smp::next_recursion>, _1, _1>();
  ut::not_invocable<smp::while_<bad_function, smp::always<_0>>, _1>();
  ut::not_invocable<smp::while_<smp::always<_1>, bad_function>, _1>();
}

TEST_SUITE_END()
