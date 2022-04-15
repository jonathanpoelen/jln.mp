#include "test/test_context.hpp"
#include "test/test_case.hpp"
#include "test/is_same.hpp"

#include "jln/mp/functional/try.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  test_unary_pack<try_, identity>();
  test_unary_pack<try_, identity, identity>();

  ut::invoke_r<int, try_<identity>, int>();
  ut::invoke_r<int&, try_<identity>, int&>();
  ut::invoke_r<int&&, try_<identity>, int&&>();

  ut::invoke_r<const int, try_<identity>, const int>();
  ut::invoke_r<const int&, try_<identity>, const int&>();
  ut::invoke_r<const int&&, try_<identity>, const int&&>();

  ut::invoke_r<na, try_<identity>, int, int>();
}

TEST_SUITE_END()
