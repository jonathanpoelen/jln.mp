#pragma once

#define TEST() TEST_I(__COUNTER__)
#define TEST_I(n) TEST_II(n)
#define TEST_II(n) inline void test_ ## n()

int main()
{}
