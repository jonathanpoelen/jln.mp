#pragma once

#include "jln/cxx/diagnostic.hpp"

#define TEST_SUITE_BEGIN() TEST_SUITE_BEGIN_I(jln_test_, __COUNTER__)
#define TEST_SUITE_BEGIN_I(name, n) TEST_SUITE_BEGIN_II(name, n)
#define TEST_SUITE_BEGIN_II(name, n) \
  namespace { struct test_ ## name ## _ ## n {
#define TEST_SUITE_END() }; }

#define TEST() TEST_I(__COUNTER__)
#define TEST_I(n) TEST_II(n)

#ifdef __clang__
  #define TEST_II(n)                                 \
    JLN_DIAGNOSTIC_PUSH                              \
    JLN_DIAGNOSTIC_CLANG_IGNORE("-Wunused-member-function") \
    inline void test_ ## n()                         \
    JLN_DIAGNOSTIC_POP
#else
  #define TEST_II(n) inline void test_ ## n()
#endif

int main()
{}
