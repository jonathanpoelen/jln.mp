// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test/test_context.hpp"
#include "test/is_invocable.hpp"
#include "test/is_same.hpp"
#include "test/test_case.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/make_id.hpp"

#ifdef __cpp_generic_lambdas
#if __cpp_generic_lambdas >= 201707L

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<make_id>();
  test_unary_pack<make_id_for, void>();

  ut::same<detail::sfinae<make_id<>>, smp::make_id<>>();

  using emp::id_of_v;
  using emp::id_of;


  static_assert(id_of_v<int> == 0);
  id_of<int>() = _0();

  static_assert(id_of_v<long> == 1);
  id_of<long>() = _1();

  id_of<char>() = _2();
  static_assert(id_of_v<char> == 2);

  id_of<int>() = _0();
  static_assert(id_of_v<int> == 0);

  class tag1;

  static_assert(id_of_v<int, tag1> == 0);
  id_of<int, tag1>() = _0();

  static_assert(id_of_v<long, tag1> == 1);
  id_of<long, tag1>() = _1();

  id_of<char, tag1>() = _2();
  static_assert(id_of_v<char, tag1> == 2);

  id_of<int, tag1>() = _0();
  static_assert(id_of_v<int, tag1> == 0);


  class tag2;

  make_id_for<tag2>::f<int>() = _0();
  make_id_for<tag2>::f<int>() = _0();
  smp::make_id_for<tag2>::f<int>() = _0();
  smp::make_id_for<tag2>::f<int>() = _0();

  make_id_for<tag2>::f<long>() = _1();
  make_id_for<tag2>::f<long>() = _1();
  smp::make_id_for<tag2>::f<long>() = _1();
  smp::make_id_for<tag2>::f<long>() = _1();

  make_id_for<tag2>::f<void>() = _2();
  make_id_for<tag2>::f<void>() = _2();
  smp::make_id_for<tag2>::f<void>() = _2();
  smp::make_id_for<tag2>::f<void>() = _2();


  make_id<>::f<long>() = _1();
  make_id<>::f<long>() = _1();
  smp::make_id<>::f<long>() = _1();
  smp::make_id<>::f<long>() = _1();

  make_id<>::f<int>() = _0();
  make_id<>::f<int>() = _0();
  smp::make_id<>::f<int>() = _0();
  smp::make_id<>::f<int>() = _0();

  make_id<>::f<void>() = _3();
  make_id<>::f<void>() = _3();
  smp::make_id<>::f<void>() = _3();
  smp::make_id<>::f<void>() = _3();


  ut::not_invocable<smp::make_id_for<tag2>>();
  ut::not_invocable<smp::make_id_for<tag2>, int, int>();
  ut::not_invocable<smp::make_id_for<tag2, bad_function>, int>();

  static_assert(emp::next_id_v<> != emp::next_id_v<>);
}

TEST_SUITE_END()

#endif
#endif
