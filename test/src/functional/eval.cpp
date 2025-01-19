// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test/test_case.hpp"

#if JLN_MP_FEATURE_NONTYPE_TEMPLATE_CLASS

#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/functional/eval.hpp"
#include "jln/mp/smp/list/push_front.hpp"
#include "jln/mp/smp/list/listify.hpp"

TEST_SUITE_BEGIN()

JLN_MP_DIAGNOSTIC_PUSH()
JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wunused-template")
JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wunused-member-function")

struct foo
{
  template<class T>
  T operator()() const
  {
    return T{};
  }
};

struct bar
{
  template<class T, class U>
  T operator()() const
  {
    return T{};
  }
};

struct NoTpl
{
  int operator()() const
  {
    return int{};
  }
};

struct NoConst
{
  template<class T>
  T operator()()
  {
    return T{};
  }
};

struct Noop { };

JLN_MP_DIAGNOSTIC_POP()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<int, emp::eval<foo{}, int>>();

  test_context<eval<foo{}>, smp::eval<foo{}>>()
    .test<int, int>()
    .not_invocable<>()
    .not_invocable<int, int>()
    ;

  test_context<eval<bar{}>, smp::eval<bar{}>>()
    .test<int, int, char>()
    .test<char, char, int>()
    .not_invocable<>()
    .not_invocable<int>()
    ;

  ut::not_invocable<smp::eval<Noop{}>>();
  ut::not_invocable<smp::eval<NoTpl{}>>();
  ut::not_invocable<smp::eval<NoConst{}>, int>();
}

TEST_SUITE_END()
#endif
