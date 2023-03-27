#pragma once

#include "jln/mp/detail/compiler.hpp"

#define TEST_SUITE_BEGIN() TEST_SUITE_BEGIN_I(jln_test_, __COUNTER__)
#define TEST_SUITE_BEGIN_I(name, n) TEST_SUITE_BEGIN_II(name, n)
// under namespace to prevent ambiguities with libc
#define TEST_SUITE_BEGIN_II(name, n) \
  namespace jln { namespace { namespace test_suite { struct test_ ## name ## n {
#define TEST_SUITE_END() }; } } }

#define TEST() TEST_I(__COUNTER__)
#define TEST_I(n) TEST_II(n)

#if JLN_MP_CLANG_LIKE
  #define TEST_II(n)                                           \
    JLN_MP_DIAGNOSTIC_PUSH()                                   \
    JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wunused-member-function") \
    inline void test_ ## n()                                   \
    JLN_MP_DIAGNOSTIC_POP()
#else
  #define TEST_II(n) inline void test_ ## n()
#endif

int main()
{}
