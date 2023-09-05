// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/insert_sequence.hpp"

TEST_SUITE_BEGIN()

template<class...> class other_list;

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<insert_sequence, _1, list<>>();

  ut::same<emp::numbers<0, 3, 1, 2>,
    emp::insert_sequence_c<seq_0_1_2, 1, list<_3>>>();

  test_context<insert_sequence_c<2, list<_6, _7>>, smp::insert_sequence_c<2, list<_6, _7>>>()
    .test<list<_0, _1, _6, _7, _2, _3>, _0, _1, _2, _3>()
    .test<list<_0, _1, _6, _7>, _0, _1>()
    .test<list<_0, _6, _7>, _0>()
    .test<list<_6, _7>>()
    ;

  test_context<insert_sequence_c<-1, list<_6, _7>>, smp::insert_sequence_c<-1, list<_6, _7>>>()
    .test<list<_0, _1, _2, _6, _7, _3>, _0, _1, _2, _3>()
    .test<list<_0, _6, _7, _1>, _0, _1>()
    .test<list<_6, _7, _0>, _0>()
    .test<list<_6, _7>>()
    ;

  test_context<insert_sequence_c<0, list<_6, _7>>, smp::insert_sequence_c<0, list<_6, _7>>>()
    .test<list<_6, _7, _0, _1, _2, _3>, _0, _1, _2, _3>()
    .test<list<_6, _7, _0, _1>, _0, _1>()
    .test<list<_6, _7, _0>, _0>()
    .test<list<_6, _7>>()
    ;

  test_context<insert_sequence_c<0, other_list<_6, _7>>, smp::insert_sequence_c<0, other_list<_6, _7>>>()
    .test<list<_6, _7, _0, _1, _2, _3>, _0, _1, _2, _3>()
    .test<list<_6, _7, _0, _1>, _0, _1>()
    .test<list<_6, _7, _0>, _0>()
    .test<list<_6, _7>>()
    ;

  ut::not_invocable<smp::insert_sequence<_2, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::insert_sequence<bad_number, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
