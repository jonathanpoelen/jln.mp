#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/value/val.hpp>

#include <jln/mp/detail/compiler.hpp>

JLN_MP_DIAGNOSTIC_PUSH()
JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wlogical-op")

namespace jln::mp
{
  /// \ingroup value

  template<class C = identity>
  struct val_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE((C), val<(false || ... || xs::value)>);
  };

  template<class C = identity>
  struct val_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE((C), val<(true && ... && xs::value)>);
  };

  template<class C = identity>
  struct val_add
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE((C), val<(... + xs::value)>);
  };

  template<class C = identity>
  using val_add0 = if_<size<>, val_add<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_sub
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE((C), val<(... - xs::value)>);
  };

  template<class C = identity>
  using val_sub0 = if_<size<>, val_sub<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_lshift
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE((C), val<(... << xs::value)>);
  };

  template<class C = identity>
  using val_lshift0 = if_<size<>, val_lshift<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_rshift
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE((C), val<(... >> xs::value)>);
  };

  template<class C = identity>
  using val_rshift0 = if_<size<>, val_rshift<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_mul
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE((C), val<(... * xs::value)>);
  };

  template<class C = identity>
  using val_mul0 = if_<size<>, val_mul<C>, always<val<0>, C>>;

  template<class C = identity>
  using val_mul1 = if_<size<>, val_mul<C>, always<val<1>, C>>;

  template<class C = identity>
  struct val_div
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE((C), val<(... / xs::value)>);
  };

  template<class C = identity>
  using val_div0 = if_<size<>, val_div<C>, always<val<0>, C>>;

  template<class C = identity>
  using val_div1 = if_<size<>, val_div<C>, always<val<1>, C>>;

  template<class C = identity>
  struct val_mod
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE((C), val<(... % xs::value)>);
  };

  template<class C = identity>
  using val_mod0 = if_<size<>, val_mod<C>, always<val<0>, C>>;

  template<class C = identity>
  using val_mod1 = if_<size<>, val_mod<C>, always<val<1>, C>>;

  template<class C = identity>
  struct val_xor
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE((C), val<(... ^ xs::value)>);
  };

  template<class C = identity>
  using val_xor0 = if_<size<>, val_xor<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_bit_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE((C), val<(... & xs::value)>);
  };

  template<class C = identity>
  using val_bit_and0 = if_<size<>, val_bit_and<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_bit_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE((C), val<(... | xs::value)>);
  };

  template<class C = identity>
  using val_bit_or0 = if_<size<>, val_bit_or<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_neg
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE((C), val<(-x::value)>);
  };

  template<class C = identity>
  struct val_unary_plus
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE((C), val<(+x::value)>);
  };

  template<class C = identity>
  struct val_not
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE((C), val<(!x::value)>);
  };

  template<class C = identity>
  struct val_bit_not
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE((C), val<(~x::value)>);
  };

  template<class C = identity>
  struct val_inc
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE((C), val<(x::value+1)>);
  };

  template<class C = identity>
  struct val_dec
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE((C), val<(x::value-1)>);
  };

  template<class C = identity>
  struct val_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE((C), val<(x::value == y::value)>);
  };

  template<class C = identity>
  struct val_not_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE((C), val<(x::value != y::value)>);
  };

  template<class C = identity>
  struct val_less
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE((C), val<(x::value < y::value)>);
  };

  template<class C = identity>
  struct val_less_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE((C), val<(x::value <= y::value)>);
  };

  template<class C = identity>
  struct val_greater
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE((C), val<(x::value > y::value)>);
  };

  template<class C = identity>
  struct val_greater_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE((C), val<(x::value >= y::value)>);
  };


  template<class N, class C = identity>
  using val_equal_to = push_back<N, val_equal<C>>;

  template<class N, class C = identity>
  using val_not_equal_to = push_back<N, val_not_equal<C>>;

  template<class N, class C = identity>
  using val_less_than = push_back<N, val_less<C>>;

  template<class N, class C = identity>
  using val_less_equal_than = push_back<N, val_less_equal<C>>;

  template<class N, class C = identity>
  using val_greater_than = push_back<N, val_greater<C>>;

  template<class N, class C = identity>
  using val_greater_equal_than = push_back<N, val_greater_equal<C>>;


  template<auto x, class C = identity>
  using val_equal_to_c = val_equal_to<val<x>, C>;

  template<auto x, class C = identity>
  using val_not_equal_to_c = val_not_equal_to<val<x>, C>;

  template<auto x, class C = identity>
  using val_less_than_c = val_less_than<val<x>, C>;

  template<auto x, class C = identity>
  using val_less_equal_than_c = val_less_equal_than<val<x>, C>;

  template<auto x, class C = identity>
  using val_greater_than_c = val_greater_than<val<x>, C>;

  template<auto x, class C = identity>
  using val_greater_equal_than_c = val_greater_equal_than<val<x>, C>;
}

namespace jln::mp::emp
{
  template<class L, class C = mp::identity>
  using val_or_seq = unpack<L, mp::val_or<C>>;

  template<class L, class C = mp::identity>
  using val_and_seq = unpack<L, mp::val_and<C>>;

  template<class L, class C = mp::identity>
  using val_add_seq = unpack<L, mp::val_add<C>>;

  template<class L, class C = mp::identity>
  using val_add0_seq = unpack<L, mp::val_add0<C>>;

  template<class L, class C = mp::identity>
  using val_sub_seq = unpack<L, mp::val_sub<C>>;

  template<class L, class C = mp::identity>
  using val_sub0_seq = unpack<L, mp::val_sub0<C>>;

  template<class L, class C = mp::identity>
  using val_lshift_seq = unpack<L, mp::val_lshift<C>>;

  template<class L, class C = mp::identity>
  using val_lshift0_seq = unpack<L, mp::val_lshift0<C>>;

  template<class L, class C = mp::identity>
  using val_rshift_seq = unpack<L, mp::val_rshift<C>>;

  template<class L, class C = mp::identity>
  using val_rshift0_seq = unpack<L, mp::val_rshift0<C>>;

  template<class L, class C = mp::identity>
  using val_mul_seq = unpack<L, mp::val_mul<C>>;

  template<class L, class C = mp::identity>
  using val_mul0_seq = unpack<L, mp::val_mul0<C>>;

  template<class L, class C = mp::identity>
  using val_mul1_seq = unpack<L, mp::val_mul1<C>>;

  template<class L, class C = mp::identity>
  using val_div_seq = unpack<L, mp::val_div<C>>;

  template<class L, class C = mp::identity>
  using val_div0_seq = unpack<L, mp::val_div0<C>>;

  template<class L, class C = mp::identity>
  using val_div1_seq = unpack<L, mp::val_div1<C>>;

  template<class L, class C = mp::identity>
  using val_mod_seq = unpack<L, mp::val_mod<C>>;

  template<class L, class C = mp::identity>
  using val_mod0_seq = unpack<L, mp::val_mod0<C>>;

  template<class L, class C = mp::identity>
  using val_mod1_seq = unpack<L, mp::val_mod1<C>>;

  template<class L, class C = mp::identity>
  using val_xor_seq = unpack<L, mp::val_xor<C>>;

  template<class L, class C = mp::identity>
  using val_xor0_seq = unpack<L, mp::val_xor0<C>>;

  template<class L, class C = mp::identity>
  using val_bit_and_seq = unpack<L, mp::val_bit_and<C>>;

  template<class L, class C = mp::identity>
  using val_bit_and0_seq = unpack<L, mp::val_bit_and0<C>>;

  template<class L, class C = mp::identity>
  using val_bit_or_seq = unpack<L, mp::val_bit_or<C>>;

  template<class L, class C = mp::identity>
  using val_bit_or0_seq = unpack<L, mp::val_bit_or0<C>>;


  template<auto... xs>
  using val_or_c = val<(false || ... || xs)>;

  template<auto... xs>
  using val_and_c = val<(true && ... && xs)>;

  template<auto... xs>
  using val_add_c = val<(... + xs)>;

  template<auto... xs>
  using val_add0_c = val_add_c<xs..., 0>;

  template<auto... xs>
  using val_sub_c = val<(... - xs)>;

  template<auto... xs>
  using val_sub0_c = val_sub_c<xs..., 0>;

  template<auto... xs>
  using val_lshift_c = val<(... << xs)>;

  template<auto... xs>
  using val_lshift0_c = val_lshift_c<xs..., 0>;

  template<auto... xs>
  using val_rshift_c = val<(... >> xs)>;

  template<auto... xs>
  using val_rshift0_c = val_rshift_c<xs..., 0>;

  template<auto... xs>
  using val_mul_c = val<(... * xs)>;

  template<auto... xs>
  using val_mul0_c = val_mul_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<auto... xs>
  using val_mul1_c = val_mul_c<xs..., 1>;

  template<auto... xs>
  using val_div_c = val<(... / xs)>;

  template<auto... xs>
  using val_div0_c = val_div_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<auto... xs>
  using val_div1_c = val_div_c<xs..., 1>;

  template<auto... xs>
  using val_mod_c = val<(... % xs)>;
}

/// \cond
namespace jln::mp::detail
{
  template<bool, template<auto...> class f, int_ d>
  struct val_emp_op;

  template<template<auto...> class F, int_ d>
  struct val_emp_op<true, F, d>
  {
    template<auto... xs>
    using f = F<xs...>;
  };

  template<template<auto...> class F, int_ d>
  struct val_emp_op<false, F, d>
  {
    template<auto...>
    using f = val<d>;
  };
}
/// \endcond

namespace jln::mp::emp
{
  template<auto... xs>
  using val_mod0_c = typename detail::val_emp_op<sizeof...(xs) != 0, val_mod_c, 0>
    ::template f<xs...>;

  template<auto... xs>
  using val_mod1_c = typename detail::val_emp_op<sizeof...(xs) != 0, val_mod_c, 1>
    ::template f<xs...>;

  template<auto... xs>
  using val_xor_c = val<(... ^ xs)>;

  template<auto... xs>
  using val_xor0_c = val_xor_c<xs..., 0, 0>;

  template<auto... xs>
  using val_bit_and_c = val<(... & xs)>;

  template<auto... xs>
  using val_bit_and0_c = typename detail::val_emp_op<sizeof...(xs) != 0, val_bit_and_c, 0>
    ::template f<xs...>;

  template<auto... xs>
  using val_bit_or_c = val<(... | xs)>;

  template<auto... xs>
  using val_bit_or0_c = typename detail::val_emp_op<sizeof...(xs) != 0, val_bit_or_c, 0>
    ::template f<xs...>;


  template<class... xs>
  using val_or = val<(false || ... || xs::value)>;

  template<class... xs>
  using val_and = val<(true && ... && xs::value)>;

  template<class... xs>
  using val_add = val<(... + xs::value)>;

  template<class... xs>
  using val_add0 = typename mp::val_add0<>::template f<xs...>;

  template<class... xs>
  using val_sub = val<(... - xs::value)>;

  template<class... xs>
  using val_sub0 = typename mp::val_sub0<>::template f<xs...>;

  template<class... xs>
  using val_lshift = val<(... << xs::value)>;

  template<class... xs>
  using val_lshift0 = typename mp::val_lshift0<>::template f<xs...>;

  template<class... xs>
  using val_rshift = val<(... >> xs::value)>;

  template<class... xs>
  using val_rshift0 = typename mp::val_rshift0<>::template f<xs...>;

  template<class... xs>
  using val_mul = val<(... * xs::value)>;

  template<class... xs>
  using val_mul0 = typename mp::val_mul0<>::template f<xs...>;

  template<class... xs>
  using val_mul1 = typename mp::val_mul1<>::template f<xs...>;

  template<class... xs>
  using val_div = val<(... / xs::value)>;

  template<class... xs>
  using val_div0 = typename mp::val_div0<>::template f<xs...>;

  template<class... xs>
  using val_div1 = typename mp::val_div1<>::template f<xs...>;

  template<class... xs>
  using val_mod = val<(... % xs::value)>;

  template<class... xs>
  using val_mod0 = typename mp::val_mod0<>::template f<xs...>;

  template<class... xs>
  using val_mod1 = typename mp::val_mod1<>::template f<xs...>;

  template<class... xs>
  using val_xor = val<(... ^ xs::value)>;

  template<class... xs>
  using val_xor0 = typename mp::val_xor0<>::template f<xs...>;

  template<class... xs>
  using val_bit_and = val<(... & xs::value)>;

  template<class... xs>
  using val_bit_and0 = typename mp::val_bit_and0<>::template f<xs...>;

  template<class... xs>
  using val_bit_or = val<(... | xs::value)>;

  template<class... xs>
  using val_bit_or0 = typename mp::val_bit_or0<>::template f<xs...>;


  template<class x, class C = mp::identity>
  using val_neg = typename mp::val_neg<C>::template f<x>;

  template<class x, class C = mp::identity>
  using val_unary_plus = typename mp::val_unary_plus<C>::template f<x>;

  template<class x, class C = mp::identity>
  using val_not = typename mp::val_not<C>::template f<x>;

  template<class x, class C = mp::identity>
  using val_bit_not = typename mp::val_bit_not<C>::template f<x>;

  template<class x, class C = mp::identity>
  using val_inc = typename mp::val_inc<C>::template f<x>;

  template<class x, class C = mp::identity>
  using val_dec = typename mp::val_dec<C>::template f<x>;

  template<class x, class y, class C = mp::identity>
  using val_equal = typename mp::val_equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using val_not_equal = typename mp::val_not_equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using val_less = typename mp::val_less<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using val_less_equal = typename mp::val_less_equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using val_greater = typename mp::val_greater<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using val_greater_equal = typename mp::val_greater_equal<C>::template f<x, y>;
}

JLN_MP_DIAGNOSTIC_POP()
