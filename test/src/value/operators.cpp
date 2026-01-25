// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/unpack.hpp"
#include "jln/mp/smp/value/operators.hpp"

#include <type_traits>

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using e = list<>;

  using yes = val<true>;
  using no = val<false>;

  ut::same<yes, emp::val_and_seq<e>>();
  ut::same<no, emp::val_or_seq<e>>();
  ut::same<yes, emp::val_or_seq<seq_1_1_1>>();
  ut::same<no, emp::val_or_seq<seq_0_0_0>>();

  ut::same<yes, emp::val_or<_0, _1, _0>>();
  ut::same<no, emp::val_or<>>();
  ut::same<no, emp::val_and<_0, _1, _0>>();
  ut::same<yes, emp::val_and<>>();

  ut::same<no, emp::val_not<yes>>();

  ut::same<yes, emp::val_or_c<0, 1, 0>>();
  ut::same<no, emp::val_or_c<>>();
  ut::same<no, emp::val_and_c<0, 1, 0>>();
  ut::same<yes, emp::val_and_c<>>();


  test_unary_pack<val_or>();

  auto ctx = [](auto f){
    using g = unpack<decltype(f)>;
    return test_context<g, detail::sfinae<g>>();
  };

  ctx(val_or<>())
    .test<no, e>()
    .test<no, seq_0_0_0>()
    .test<yes, seq_1_1_1>()
    .not_invocable<seq_bad>()
    .not_invocable<seq_bad_bad>()
    ;

  ctx(val_and<>())
    .test<yes, e>()
    .test<no, seq_0_0_0>()
    .test<yes, seq_1_1_1>()
    ;

  ctx(val_div<>())
    .test<val<int_t(42)>, list<_42>>()
    .test<val<int_t(1)>, seq_1_1_1>()
    .test<val<int_t(0)>, seq_0_1_2>()
    .test<val<int_t(0)>, seq_1_2_3>()
    .test<val<int_t(1)>, seq_3_2_1>()
    .not_invocable<e>()
    .not_invocable<seq_2_1_0>()
    .not_invocable<seq_0_0_0>()
    ;

  ctx(val_add0<>())
    .test<val<0>, e>()
    .test<val<int_t(0)>, seq_0_0_0>()
    .test<val<int_t(3)>, seq_1_1_1>()
    ;

  ut::invoke_r<val<0>, val_div0<>>();
  ut::invoke_r<val<int_t(1)>, val_div0<>, _1>();
  // FIX gcc7: val<0> is a typed_value<int_t,0> if val<int_t(0)> precedes val<0>
  if constexpr (std::is_same_v<val<0>, typed_value<int,0>>) {
    ut::invoke_r<val<0>, smp::val_div0<>>();
    ut::invoke_r<val<1>, smp::val_div1<>>();
  }
  ut::invoke_r<val<int_t(0)>, smp::val_div0<>, _0>();
  ut::invoke_r<val<int_t(1)>, smp::val_div0<>, _1>();
  ut::invoke_r<val<int_t(2)>, smp::val_div0<>, _2>();
  ut::not_invocable<smp::val_div0<>, _1, _0>();
  ut::invoke_r<val<1>, smp::val_div0<val_inc<>>>();
  ut::invoke_r<val<2>, smp::val_div1<val_inc<>>>();

  ut::invoke_r<val<true>, smp::val_equal_to<_3>, _3>();
  ut::invoke_r<val<false>, smp::val_not_equal_to<_3>, _3>();
  ut::invoke_r<val<true>, smp::val_less_than<_3>, _2>();
  ut::invoke_r<val<true>, smp::val_less_equal_than<_3>, _3>();
  ut::invoke_r<val<true>, smp::val_greater_than<_1>, _3>();
  ut::invoke_r<val<true>, smp::val_greater_equal_than<_3>, _3>();

  test_context<val_not<>, smp::val_not<>>()
    .test<val<true>, _0>()
    .test<val<false>, _1>()
    .not_invocable<e>()
    ;

  ut::not_invocable<smp::val_not<bad_function>>();
  ut::not_invocable<smp::val_not<bad_function>, no>();
  ut::not_invocable<smp::val_div0<bad_function>>();
  ut::not_invocable<smp::val_div0<bad_function>, _1, _1>();
}

TEST_SUITE_END()
