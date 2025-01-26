// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test/test_context.hpp"
#include "test/is_invocable.hpp"
#include "test/is_same.hpp"
#include "test/test_case.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/make_index.hpp"

#if JLN_MP_ENABLE_FRIEND_INJECTION && JLN_MP_FEATURE_CONCEPTS

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<make_index>();
  test_unary_pack<make_index_for, void>();

  ut::same<detail::sfinae<make_index<>>, smp::make_index<>>();

  using emp::index_of_v;
  using emp::index_of;


  static_assert(index_of_v<int> == 0);
  index_of<int>() = _0();

  static_assert(index_of_v<long> == 1);
  index_of<long>() = _1();

  index_of<char>() = _2();
  static_assert(index_of_v<char> == 2);

  index_of<int>() = _0();
  static_assert(index_of_v<int> == 0);

  class tag1;

  static_assert(index_of_v<int, tag1> == 0);
  index_of<int, tag1>() = _0();

  static_assert(index_of_v<long, tag1> == 1);
  index_of<long, tag1>() = _1();

  index_of<char, tag1>() = _2();
  static_assert(index_of_v<char, tag1> == 2);

  index_of<int, tag1>() = _0();
  static_assert(index_of_v<int, tag1> == 0);


  class tag2;

  make_index_for<tag2>::f<int>() = _0();
  make_index_for<tag2>::f<int>() = _0();
  smp::make_index_for<tag2>::f<int>() = _0();
  smp::make_index_for<tag2>::f<int>() = _0();

  make_index_for<tag2>::f<long>() = _1();
  make_index_for<tag2>::f<long>() = _1();
  smp::make_index_for<tag2>::f<long>() = _1();
  smp::make_index_for<tag2>::f<long>() = _1();

  make_index_for<tag2>::f<void>() = _2();
  make_index_for<tag2>::f<void>() = _2();
  smp::make_index_for<tag2>::f<void>() = _2();
  smp::make_index_for<tag2>::f<void>() = _2();


  make_index<>::f<long>() = _1();
  make_index<>::f<long>() = _1();
  smp::make_index<>::f<long>() = _1();
  smp::make_index<>::f<long>() = _1();

  make_index<>::f<int>() = _0();
  make_index<>::f<int>() = _0();
  smp::make_index<>::f<int>() = _0();
  smp::make_index<>::f<int>() = _0();

  make_index<>::f<void>() = _3();
  make_index<>::f<void>() = _3();
  smp::make_index<>::f<void>() = _3();
  smp::make_index<>::f<void>() = _3();


  ut::not_invocable<smp::make_index_for<tag2>>();
  ut::not_invocable<smp::make_index_for<tag2>, int, int>();
  ut::not_invocable<smp::make_index_for<tag2, bad_function>, int>();

  static_assert(emp::next_index_v<> != emp::next_index_v<>);
}

TEST_SUITE_END()

#endif
