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
  test_unary_pack<try_or_else, identity>();
  test_unary_pack<is_invocable>();
  test_unary_pack<is_not_invocable>();

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

  // try_or_else

  ut::invoke_r<int, try_or_else<identity>, int>();
  ut::invoke_r<na, try_or_else<identity>>();
  ut::invoke_r<int, try_or_else<identity, always<no>>, int>();
  ut::invoke_r<no, try_or_else<identity, always<no>>>();

  ut::same<int, emp::try_or_else<identity, always<no>, int>>();
  ut::same<no, emp::try_or_else<identity, always<no>>>();

  // try_or

  ut::invoke_r<int, try_or<identity>, int>();
  ut::invoke_r<na, try_or<identity>>();
  ut::invoke_r<int, try_or<identity, always<no>>, int>();
  ut::invoke_r<always<no>, try_or<identity, always<no>>>();

  ut::same<int, emp::try_or<identity, always<no>, int>>();
  ut::same<always<no>, emp::try_or<identity, always<no>>>();

  // is_invocable

  ut::invoke_r<true_, is_invocable<identity>, int>();
  ut::invoke_r<false_, is_invocable<identity>>();

  ut::same<true_, emp::is_invocable<identity, int>>();
  ut::same<false_, emp::is_invocable<identity, int, int>>();

  number<emp::is_invocable_v<identity>>() = false_();
  number<emp::is_invocable_v<identity, int>>() = true_();

  // is_not_invocable

  ut::invoke_r<false_, is_not_invocable<identity>, int>();
  ut::invoke_r<true_, is_not_invocable<identity>>();

  ut::same<false_, emp::is_not_invocable<identity, int>>();
  ut::same<true_, emp::is_not_invocable<identity, int, int>>();

  number<emp::is_not_invocable_v<identity>>() = true_();
  number<emp::is_not_invocable_v<identity, int>>() = false_();
}

JLN_MP_DIAGNOSTIC_PUSH()
JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wunused-const-variable")
#if JLN_MP_CLANG >= 1800
JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wunused-template")
#endif
struct A;
struct B { template<class> using f = int; };
struct C { template<int> using f = int; };
struct D { template<class x> using f = typename x::type; };
struct E { template<class x> static constexpr int f = x::value; };
struct F { template<class...> using f = int; };
struct G { template<class...> static constexpr int f = 1; };
struct H { template<int...> using f = int; };
struct I { template<int...> static constexpr int f = 1; };

struct t { using type = int; };
struct v { static constexpr int value = 1; };
JLN_MP_DIAGNOSTIC_POP()

template<class... xs, class a, class b, class c, class d, class e, class f, class g, class h, class i>
void invoke(a, b, c, d, e, f, g, h, i)
{
  using jln::mp::is_invocable;

  a{} = is_invocable<A>::f<xs...>{};
  b{} = is_invocable<B>::f<xs...>{};
  c{} = is_invocable<C>::f<xs...>{};
  d{} = is_invocable<D>::f<xs...>{};
  e{} = is_invocable<E>::f<xs...>{};
  f{} = is_invocable<F>::f<xs...>{};
  g{} = is_invocable<G>::f<xs...>{};
  h{} = is_invocable<H>::f<xs...>{};
  i{} = is_invocable<I>::f<xs...>{};
}

TEST()
{
  using namespace jln::mp;

  test_mulary_pack<is_invocable>();
  test_mulary_pack<is_invocable, identity>();

  auto y = true_{};
  auto n = false_{};

  //          A  B  C  D  E  F  G  H  I
  invoke<   >(n, n, n, n, n, y, n, y, n);
  invoke<int>(n, y, n, n, n, y, n, n, n);
  invoke<t  >(n, y, n, y, n, y, n, n, n);
  invoke<v  >(n, y, n, n, n, y, n, n, n);
}

TEST_SUITE_END()
