#pragma once

#include "jln/cxx/diagnostic.hpp"

#define TEST_SUITE_BEGIN(name) TEST_SUITE_BEGIN_I(name, __COUNTER__)
#define TEST_SUITE_BEGIN_I(name, n) TEST_SUITE_BEGIN_II(name, n)
#define TEST_SUITE_BEGIN_II(name, n) \
  namespace { struct test_ ## name ## _ ## n {
#define TEST_SUITE_END() }; }

#define TEST() TEST_I(__COUNTER__)
#define TEST_I(n) TEST_II(n)

#ifdef __clang__
  #define TEST_II(n)                                 \
    JLN_DIAGNOSTIC_PUSH                              \
    JLN_DIAGNOSTIC_CLANG_IGNORE("-Wunused-function") \
    inline void test_ ## n()                         \
    JLN_DIAGNOSTIC_POP
#else
  #define TEST_II(n) inline void test_ ## n()
#endif

#define IGNORE_UNUSED_FUNCTION_PUSH()                            \
  JLN_DIAGNOSTIC_PUSH                                            \
  JLN_DIAGNOSTIC_CLANG_IGNORE("-Wunused-template")               \
  JLN_DIAGNOSTIC_CLANG_IGNORE("-Wunneeded-internal-declaration") \
  JLN_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wunused-function")            \

#define IGNORE_UNUSED_FUNCTION_POP() JLN_DIAGNOSTIC_POP

int main()
{}
