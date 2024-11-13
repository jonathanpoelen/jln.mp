// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test/test_case.hpp"

#include "jln/mp/utility/lazy_void.hpp"

TEST_SUITE_BEGIN()

template<class T, class = jln::mp::list<>> struct X;
template<class T> struct X<T, jln::mp::emp::lazy_void<typename T::foo>> {};
// using std::lazy_void causes redefinition error with clang
template<class T> struct X<T, jln::mp::emp::lazy_void<typename T::bar>> {};

TEST_SUITE_END()
