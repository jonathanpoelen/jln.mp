// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/contains.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<contains, void>();

  ut::same<true_, emp::contains<seq_0_1_2, _1>>();
  ut::same<false_, emp::contains<seq_0_1_2, _3>>();

  test_context<contains<_1>, smp::contains<_1>, 0>()
    .test<false_>()
    .test<false_, _0>()
    .test<true_, _1>()
    .test<true_, _1, _1, _1>()
    .test<false_, _0, _0, _0>()
    .test<true_, _0, _0, _1>()
    ;

  ut::not_invocable<smp::contains<void, bad_function>, void>();
}

TEST_SUITE_END()
