// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/size.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/algorithm/repeat.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<repeat, _1>();

  ut::same<seq_1_1_1, emp::repeat_c<seq_1, 3>>();

  test_context<repeat_c<0>, smp::repeat_c<0>>()
    .test<list<>>()
    .test<list<>, _1>()
    .test<list<>, _1, _2>()
    .test<list<>, _1, _2, _3>()
    ;

  test_context<repeat_c<1>, smp::repeat_c<1>>()
    .test<list<>>()
    .test<seq_1, _1>()
    .test<seq_1_2, _1, _2>()
    .test<seq_1_2_3, _1, _2, _3>()
    ;

  test_context<repeat_c<3>, smp::repeat_c<3>>()
    .test<list<>>()
    .test<seq_1_1_1, _1>()
    .test<list<_1, _2, _1, _2, _1, _2>, _1, _2>()
    .test<list<_1, _2, _3, _1, _2, _3, _1, _2, _3>, _1, _2, _3>()
    ;

  test_context<repeat_c<10>, smp::repeat_c<10>>()
    .test<list<>>()
    .test<list<_1, _1, _1, _1, _1, _1, _1, _1, _1, _1>, _1>()
    .test<list<_1, _2, _1, _2, _1, _2, _1, _2, _1, _2,
               _1, _2, _1, _2, _1, _2, _1, _2, _1, _2>, _1, _2>()
    .test<list<_1, _2, _3, _1, _2, _3, _1, _2, _3,
               _1, _2, _3, _1, _2, _3, _1, _2, _3,
               _1, _2, _3, _1, _2, _3, _1, _2, _3,
               _1, _2, _3>, _1, _2, _3>()
    ;

  test_context<repeat_c<0, size<>>, smp::repeat_c<0, smp::size<>>>()
    .test<_0>()
    .test<_0, _1>()
    .test<_0, _1, _2>()
    .test<_0, _1, _2, _3>()
    ;

  test_context<repeat_c<1, size<>>, smp::repeat_c<1, smp::size<>>>()
    .test<_0>()
    .test<_1, _1>()
    .test<_2, _1, _2>()
    .test<_3, _1, _2, _3>()
    ;

  test_context<repeat_c<3, size<>>, smp::repeat_c<3, smp::size<>>>()
    .test<_0>()
    .test<_3, _1>()
    .test<_6, _1, _2>()
    .test<_9, _1, _2, _3>()
    ;

  test_context<repeat_c<10, size<>>, smp::repeat_c<10, smp::size<>>>()
    .test<_0>()
    .test<_10, _1>()
    .test<_20, _1, _2>()
    .test<_30, _1, _2, _3>()
    ;

  ut::not_invocable<smp::repeat_c<-3>>();
  ut::not_invocable<smp::repeat<smp::always<na>>>();
  ut::not_invocable<smp::repeat<_2, bad_function>>();
  ut::not_invocable<smp::repeat<_2, bad_function>, _1>();
  ut::not_invocable<smp::repeat<_2, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::repeat<bad_number, bad_function>>();
  ut::not_invocable<smp::repeat<bad_number, bad_function>, _1>();
  ut::not_invocable<smp::repeat<bad_number, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
