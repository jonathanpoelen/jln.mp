// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/number/math.hpp"
#include "jln/mp/smp/number/numbers.hpp"
#include "jln/mp/smp/utility/unpack.hpp"

TEST_SUITE_BEGIN()

template<int i>
struct num
{
  static constexpr int value = i;
};

template<class T> struct W : T {};

using int_ = jln::mp::int_;

template<int_ result, int_ a, int_ b>
static void test_min()
{
  using namespace jln::mp;
  using c = neg<>;

  ut::same<number<result>, emp::min<number<a>, number<b>>>();
  ut::same<number<result>, emp::min_c<a, b>>();
  ut::same<number<result>, number<emp::min_v<number<a>, number<b>>>>();
  ut::same<number<result>, number<emp::min_c_v<a, b>>>();

  ut::same<number<-result>, emp::min<number<a>, number<b>, c>>();
  ut::same<number<-result>, emp::min_c<a, b, c>>();
  ut::same<number<-result>, number<emp::min_v<number<a>, number<b>, c>>>();
  ut::same<number<-result>, number<emp::min_c_v<a, b, c>>>();
}

template<int_ result, int_ a, int_ b>
static void test_max()
{
  using namespace jln::mp;
  using c = neg<>;

  ut::same<number<result>, emp::max<number<a>, number<b>>>();
  ut::same<number<result>, emp::max_c<a, b>>();
  ut::same<number<result>, number<emp::max_v<number<a>, number<b>>>>();
  ut::same<number<result>, number<emp::max_c_v<a, b>>>();

  ut::same<number<-result>, emp::max<number<a>, number<b>, c>>();
  ut::same<number<-result>, emp::max_c<a, b, c>>();
  ut::same<number<-result>, number<emp::max_v<number<a>, number<b>, c>>>();
  ut::same<number<-result>, number<emp::max_c_v<a, b, c>>>();
}

template<int_ result, int_ base, int_ exponent>
static void test_pow()
{
  using namespace jln::mp;
  using c = neg<>;

  ut::same<number<result>, emp::pow<number<base>, number<exponent>>>();
  ut::same<number<result>, emp::pow_c<base, exponent>>();
  ut::same<number<result>, number<emp::pow_v<number<base>, number<exponent>>>>();
  ut::same<number<result>, number<emp::pow_c_v<base, exponent>>>();

  ut::same<number<-result>, emp::pow<number<base>, number<exponent>, c>>();
  ut::same<number<-result>, emp::pow_c<base, exponent, c>>();
  ut::same<number<-result>, number<emp::pow_v<number<base>, number<exponent>, c>>>();
  ut::same<number<-result>, number<emp::pow_c_v<base, exponent, c>>>();
}

template<int_ result, int_ i>
static void test_abs()
{
  using namespace jln::mp;
  using c = neg<>;

  ut::same<number<result>, emp::abs<number<i>>>();
  ut::same<number<result>, emp::abs_c<i>>();
  ut::same<number<result>, number<emp::abs_v<number<i>>>>();
  ut::same<number<result>, number<emp::abs_c_v<i>>>();

  ut::same<number<-result>, emp::abs<number<i>, c>>();
  ut::same<number<-result>, emp::abs_c<i, c>>();
  ut::same<number<-result>, number<emp::abs_v<number<i>, c>>>();
  ut::same<number<-result>, number<emp::abs_c_v<i, c>>>();
}

// bypasses msvc bug when TEST_CLAMP is a template function...
//  predefined C++ types (compiler internal)(397,20): error C2976: '<dummy_class_template_1>': too few template arguments
//  predefined C++ types (compiler internal)(397,20): note: see declaration of '<dummy_class_template_1>'
//  predefined C++ types (compiler internal)(397,20): note: the template instantiation context (the oldest one first) is
//  D:\a\jln.mp\jln.mp\test\src/number/math.cpp(155,3): note: see reference to function template instantiation 'void jln::`anonymous-namespace'::test_suite::test_jln_test_390::test_clamp<2,2,0,3>(void)' being compiled
//    test_clamp<2, 2, 0, 3>();
//    ^
#define TEST_CLAMP(result, i, min, max) do {                                        \
  using namespace jln::mp;                                                          \
  using c = neg<>;                                                                  \
  using I = number<i>;                                                              \
  using Min = number<min>;                                                          \
  using Max = number<max>;                                                          \
  using lt = W<less<>>;                                                             \
                                                                                    \
  ut::same<number<result>, emp::clamp<I, Min, Max>>();                              \
  ut::same<number<result>, emp::clamp_c<i, min, max>>();                            \
  ut::same<number<result>, number<emp::clamp_v<I, Min, Max>>>();                    \
  ut::same<number<result>, number<emp::clamp_c_v<i, min, max>>>();                  \
                                                                                    \
  ut::same<number<-result>, emp::clamp<I, Min, Max, c>>();                          \
  ut::same<number<-result>, emp::clamp_c<i, min, max, c>>();                        \
  ut::same<number<-result>, number<emp::clamp_v<I, Min, Max, c>>>();                \
  ut::same<number<-result>, number<emp::clamp_c_v<i, min, max, c>>>();              \
                                                                                    \
  ut::same<number<result>, emp::clamp_with<I, Min, Max>>();                         \
  ut::same<number<result>, emp::clamp_with_c<i, min, max>>();                       \
  ut::same<number<result>, number<emp::clamp_with_v<I, Min, Max>>>();               \
  ut::same<number<result>, number<emp::clamp_with_c_v<i, min, max>>>();             \
                                                                                    \
  ut::same<number<result>, emp::clamp_with<I, Min, Max, lt>>();                     \
  ut::same<number<result>, emp::clamp_with_c<i, min, max, lt>>();                   \
  ut::same<number<result>, number<emp::clamp_with_v<I, Min, Max, lt>>>();           \
  ut::same<number<result>, number<emp::clamp_with_c_v<i, min, max, lt>>>();         \
                                                                                    \
  ut::same<number<-result>, emp::clamp_with<I, Min, Max, lt, c>>();                 \
  ut::same<number<-result>, emp::clamp_with_c<i, min, max, lt, c>>();               \
  ut::same<number<-result>, number<emp::clamp_with_v<I, Min, Max, lt, c>>>();       \
  ut::same<number<-result>, number<emp::clamp_with_c_v<i, min, max, lt, c>>>();     \
                                                                                    \
  ut::same<number<-result>, emp::clamp_with<I, Min, Max, less<>, c>>();             \
  ut::same<number<-result>, emp::clamp_with_c<i, min, max, less<>, c>>();           \
  ut::same<number<-result>, number<emp::clamp_with_v<I, Min, Max, less<>, c>>>();   \
  ut::same<number<-result>, number<emp::clamp_with_c_v<i, min, max, less<>, c>>>(); \
} while (0)

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_min<1, 1, 2>();
  test_max<2, 1, 2>();
  test_abs<1, 1>();
  test_abs<1, -1>();
  TEST_CLAMP(2, 2, 0, 3);
  TEST_CLAMP(3, 5, 0, 3);
  TEST_CLAMP(0, -5, 0, 3);
  test_pow<0, 0, 1>();
  test_pow<0, 0, 2>();
  test_pow<0, 0, 3>();
  test_pow<1, 1, 0>();
  test_pow<1, 1, 1>();
  test_pow<1, 1, 2>();
  test_pow<1, 1, 3>();
  test_pow<1, 2, 0>();
  test_pow<2, 2, 1>();
  test_pow<4, 2, 2>();
  test_pow<8, 2, 3>();
  test_pow<2*2*2*2*2*2*2*2, 2, 8>();

  test_unary_pack<pow>();
  test_unary_pack<min>();
  test_unary_pack<max>();
  test_unary_pack<abs>();

  test_context<min<>, smp::min<>>()
    .test<_1, _1, _2>()
    .test<_1, _1, num<1>>()
    .not_invocable<>()
    .not_invocable<_1>()
    .not_invocable<_1, _2, _3>()
    .not_invocable<int>()
    ;

  test_context<max<>, smp::max<>>()
    .test<_2, _1, _2>()
    .test<_1, _1, num<1>>()
    .not_invocable<>()
    .not_invocable<_1>()
    .not_invocable<_1, _2, _3>()
    .not_invocable<int>()
    ;

  test_context<clamp_c<-2, 5>, smp::clamp_c<-2, 5>>()
    .test<_1, _1>()
    .test<_4, _4>()
    .test<_5, _5>()
    .test<_5, _6>()
    .test<number<-1>, number<-1>>()
    .test<number<-2>, number<-2>>()
    .test<number<-2>, number<-3>>()
    .test<num<1>, num<1>>()
    .test<num<4>, num<4>>()
    .test<num<5>, num<5>>()
    .test<_5, num<6>>()
    .test<num<-1>, num<-1>>()
    .test<num<-2>, num<-2>>()
    .test<number<-2>, num<-3>>()
    .not_invocable<>()
    .not_invocable<int>()
    .not_invocable<_1, _2>()
    .not_invocable<bad_number>()
    ;

  test_context<clamp_with_c<5, -2, greater<>>, smp::clamp_with_c<5, -2, smp::greater<>>>()
    .test<_1, _1>()
    .test<_4, _4>()
    .test<_5, _5>()
    .test<_5, _6>()
    .test<number<-1>, number<-1>>()
    .test<number<-2>, number<-2>>()
    .test<number<-2>, number<-3>>()
    .test<num<1>, num<1>>()
    .test<num<4>, num<4>>()
    .test<num<5>, num<5>>()
    .test<_5, num<6>>()
    .test<num<-1>, num<-1>>()
    .test<num<-2>, num<-2>>()
    .test<number<-2>, num<-3>>()
    .not_invocable<>()
    .not_invocable<int>()
    .not_invocable<_1, _2>()
    .not_invocable<bad_number>()
    ;

  using limits = std::numeric_limits<int_>;
  using limits2 = std::numeric_limits<int>;

  test_context<abs<>, smp::abs<>>()
    .test<_1, _1>()
    .test<_1, number<(-1)>>()
    .test<number<limits::max()>, number<limits::max()>>()
    .test<number<limits::max()>, number<limits::min() + 1>>()
    .test<num<1>, num<1>>()
    .test<_1, num<(-1)>>()
    .test<num<limits2::max()>, num<limits2::max()>>()
    .test<number<limits2::max()>, num<limits2::min() + 1>>()
    .not_invocable<>()
    .not_invocable<_1, _2>()
    .not_invocable<int>()
    .not_invocable<bad_number>()
    .not_invocable<number<limits::min()>>()
    ;

  test_context<pow<>, smp::pow<>>()
    .test<_1, _0, _0>()
    .test<_0, _0, _1>()
    .test<_1, _1, _1>()
    .test<_8, _2, _3>()
    .not_invocable<_0>()
    .not_invocable<_0, _0, _1>()
    .not_invocable<_1, _0, _0>()
    .not_invocable<bad_number, _1>()
    .not_invocable<_0, bad_number>()
    .not_invocable<int, _1>()
    .not_invocable<_0, int>()
    .not_invocable<_0, bad_number, bad_number>()
    ;

  ut::not_invocable<smp::min<bad_function>, _1, _2>();
  ut::not_invocable<smp::max<bad_function>, _1, _2>();
  ut::not_invocable<smp::abs<bad_function>, _1>();
  ut::not_invocable<smp::clamp_c<0, 3, bad_function>, _1>();
  ut::not_invocable<smp::clamp<bad_number, _2>, _1>();
  ut::not_invocable<smp::clamp<_1, bad_number>, _1>();
  ut::not_invocable<smp::clamp<void, _2>, _1>();
  ut::not_invocable<smp::clamp<_1, void>, _1>();
  ut::not_invocable<smp::pow<bad_function>>();
  ut::not_invocable<smp::pow<bad_function>, _1, _1>();
}

TEST_SUITE_END()
