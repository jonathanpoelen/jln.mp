// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/lookup.hpp"
#include "jln/mp/algorithm/make_int_sequence.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

#define SEQ int, char, void, float

  using l = list<SEQ>;

  ut::same<void, emp::lookup<l, _2>>();

  test_context<build_indexed<SEQ>, smp::build_indexed<SEQ>>()
    .test<int, _0>()
    .test<char, _1>()
    .test<void, _2>()
    .test<float, _3>()
    .not_invocable<>()
    .not_invocable<_4>()
    .not_invocable<_1, _2>()
    .not_invocable<number<-1>>()
    ;

  test_context<build_indexed<SEQ, SEQ, long, SEQ, SEQ>, smp::build_indexed<SEQ, SEQ, long, SEQ, SEQ>>()
    .test<int, _0>()
    .test<char, _1>()
    .test<void, _2>()
    .test<float, _3>()
    .test<int, _4>()
    .test<char, _5>()
    .test<void, _6>()
    .test<float, _7>()
    .test<long, _8>()
    .test<int, _9>()
    .test<char, _10>()
    .test<void, _11>()
    .test<float, _12>()
    .test<int, _13>()
    .test<char, _14>()
    .test<void, _15>()
    .test<float, _16>()
    .not_invocable<>()
    .not_invocable<_17>()
    .not_invocable<_1, _2>()
    .not_invocable<number<-1>>()
    ;

#undef SEQ

#ifndef IN_IDE_PARSER
  using b300 = emp::make_int_sequence_c<300, cfe<build_indexed_v>>;
  ut::same<number<2  >, b300::f<2>>();
  ut::same<number<100>, b300::f<100>>();
  ut::same<number<200>, b300::f<200>>();
  ut::same<number<299>, b300::f<299>>();
  ut::not_invocable<ut::sfinae<emp::make_int_sequence_c<300, cfe<build_indexed>>>::f<number<300>>>();

  using b5000 = emp::make_int_sequence_c<5000, cfe<build_indexed_v>>;
  ut::same<number<2   >, b5000::f<2>>();
  ut::same<number<100 >, b5000::f<100>>();
  ut::same<number<200 >, b5000::f<200>>();
  ut::same<number<299 >, b5000::f<299>>();
  ut::same<number<1000>, b5000::f<1000>>();
  ut::same<number<4999>, b5000::f<4999>>();
  ut::not_invocable<ut::sfinae<emp::make_int_sequence_c<5000, cfe<build_indexed>>>::f<number<5000>>>();
#endif
}

TEST_SUITE_END()
