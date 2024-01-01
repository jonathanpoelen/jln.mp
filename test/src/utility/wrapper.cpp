// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test/test_case.hpp"
#include "test/is_same.hpp"

#include "jln/mp/utility/wrapper.hpp"
#include "jln/mp/list/list.hpp"

TEST_SUITE_BEGIN()

template<class...>
struct other_list;

TEST()
{
  using namespace jln::mp;

  ut::same<lift<list>, emp::wrapper<list<int>>>();
  ut::same<lift<other_list>, emp::wrapper<other_list<int>>>();

  ut::same<list<void, char>, emp::rewrap<list<int>, void, char>>();
  ut::same<other_list<void, char>, emp::rewrap<other_list<int>, void, char>>();
}

TEST_SUITE_END()
