// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test/is_same.hpp"
#include "test/test_case.hpp"

#include "jln/mp/utility/enable_if.hpp"

TEST_SUITE_BEGIN()

template<class T, bool>
struct fn_result
{};

JLN_MP_DIAGNOSTIC_PUSH()
JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wunused-template")

template<int n, class T, class R = jln::mp::enable_if_t<(0 < n), T>>
fn_result<T, true> fn(int)
{
  return true;
}

template<int n, class T>
fn_result<T, false> fn(char)
{
  return false;
}

JLN_MP_DIAGNOSTIC_POP()

TEST()
{
  ut::same<fn_result<int, 1>, decltype(fn<1, int>(1))>();
  ut::same<fn_result<int, 0>, decltype(fn<0, int>(1))>();
  ut::same<void, jln::mp::enable_if_t<true>>();
}

TEST_SUITE_END()
