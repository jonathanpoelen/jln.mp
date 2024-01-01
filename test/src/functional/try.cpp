// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test/test_context.hpp"
#include "test/test_case.hpp"
#include "test/is_same.hpp"

#include "jln/mp/functional/try.hpp"

TEST_SUITE_BEGIN()

class yes;
class no;

TEST()
{
  using namespace jln::mp;

  test_unary_pack<try_, identity>();
  test_unary_pack<try_, identity, identity>();
  test_unary_pack<try_or, identity>();
  test_unary_pack<is_callable>();
  test_unary_pack<is_not_callable>();

  // try_

  ut::invoke_r<int, try_<identity>, int>();
  ut::invoke_r<int&, try_<identity>, int&>();
  ut::invoke_r<int&&, try_<identity>, int&&>();

  ut::invoke_r<const int, try_<identity>, const int>();
  ut::invoke_r<const int&, try_<identity>, const int&>();
  ut::invoke_r<const int&&, try_<identity>, const int&&>();

  ut::invoke_r<na, try_<identity>, int, int>();

  ut::invoke_r<yes, try_<identity, always<yes>, always<no>>, int>();
  ut::invoke_r<no, try_<identity, always<yes>, always<no>>>();

  ut::same<yes, emp::try_<identity, always<yes>, always<no>, int>>();
  ut::same<no, emp::try_<identity, always<yes>, always<no>>>();

  // try_or

  ut::invoke_r<int, try_or<identity>, int>();
  ut::invoke_r<false_, try_or<identity>>();
  ut::invoke_r<int, try_or<identity, always<no>>, int>();
  ut::invoke_r<no, try_or<identity, always<no>>>();

  ut::same<int, emp::try_or<identity, always<no>, int>>();
  ut::same<no, emp::try_or<identity, always<no>>>();

  // is_callable

  ut::invoke_r<true_, is_callable<identity>, int>();
  ut::invoke_r<false_, is_callable<identity>>();

  ut::same<true_, emp::is_callable<identity, int>>();
  ut::same<false_, emp::is_callable<identity, int, int>>();

  number<emp::is_callable_v<identity>>() = false_();
  number<emp::is_callable_v<identity, int>>() = true_();

  // is_not_callable

  ut::invoke_r<false_, is_not_callable<identity>, int>();
  ut::invoke_r<true_, is_not_callable<identity>>();

  ut::same<false_, emp::is_not_callable<identity, int>>();
  ut::same<true_, emp::is_not_callable<identity, int, int>>();

  number<emp::is_not_callable_v<identity>>() = true_();
  number<emp::is_not_callable_v<identity, int>>() = false_();
}

TEST_SUITE_END()
