#include "test/test_case.hpp"
#include "test/is_same.hpp"

#include "jln/mp/functional/try_invoke.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  ut::invoke_r<int, try_invoke<identity>, int>();
  ut::invoke_r<int&, try_invoke<identity>, int&>();
  ut::invoke_r<int&&, try_invoke<identity>, int&&>();

  ut::invoke_r<const int, try_invoke<identity>, const int>();
  ut::invoke_r<const int&, try_invoke<identity>, const int&>();
  ut::invoke_r<const int&&, try_invoke<identity>, const int&&>();

  ut::invoke_r<na, try_invoke<identity>, int, int>();
}

TEST_SUITE_END()
