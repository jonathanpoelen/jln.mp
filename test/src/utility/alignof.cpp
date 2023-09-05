// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/alignof.hpp"
#include "jln/mp/list/size.hpp"

JLN_MP_DIAGNOSTIC_PUSH()
JLN_MP_DIAGNOSTIC_MSVC_IGNORE(4324)

TEST_SUITE_BEGIN()

template<std::size_t n>
struct alignas(n) aligned {};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<alignof_>();

  ut::same<_1, emp::alignof_<aligned<1>>>();
  ut::same<_2, emp::alignof_<aligned<2>>>();
  ut::same<_4, emp::alignof_<aligned<4>>>();

  test_context<alignof_<>, smp::alignof_<>>()
    .test<_1, aligned<1>>()
    .test<_8, aligned<8>>()
    .not_invocable<>()
    .not_invocable<int, int>()
    ;

  ut::not_invocable<smp::alignof_<>, void>();
  ut::not_invocable<smp::alignof_<bad_function>>();
  ut::not_invocable<smp::alignof_<bad_function>, size<>>();
}

TEST_SUITE_END()

JLN_MP_DIAGNOSTIC_POP()
