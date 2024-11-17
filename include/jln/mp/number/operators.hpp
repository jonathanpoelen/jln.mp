// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/list/push_front.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/number/not.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/utility/unpack.hpp>

#include <jln/mp/detail/compiler.hpp>

#include <limits>

JLN_MP_DIAGNOSTIC_PUSH()
JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wlogical-op")

namespace jln::mp
{
  /// \ingroup number

  template<class C = identity>
  struct or_
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value || ... || false)>);
  };

  template<class C = identity>
  struct left_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(false || ... || xs::value)>);
  };


  template<class C = identity>
  struct and_
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value && ... && true)>);
  };

  template<class C = identity>
  struct left_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(true && ... && xs::value)>);
  };


  template<class C = identity>
  struct add
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value + ...)>);
  };

  template<class C = identity>
  using add0 = if_<size<>, add<C>, always<number<0>, C>>;

  template<class C = identity>
  struct left_add
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... + xs::value)>);
  };

  template<class C = identity>
  using left_add0 = if_<size<>, left_add<C>, always<number<0>, C>>;


  template<class C = identity>
  struct sub
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... - xs::value)>);
  };

  template<class C = identity>
  using sub0 = if_<size<>, sub<C>, always<number<0>, C>>;

  template<class C = identity>
  struct lshift
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... << xs::value)>);
  };

  template<class C = identity>
  using lshift0 = if_<size<>, lshift<C>, always<number<0>, C>>;

  template<class C = identity>
  struct rshift
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... >> xs::value)>);
  };

  template<class C = identity>
  using rshift0 = if_<size<>, rshift<C>, always<number<0>, C>>;


  template<class C = identity>
  struct mul
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value * ...)>);
  };

  template<class C = identity>
  using mul0 = if_<size<>, mul<C>, always<number<0>, C>>;

  template<class C = identity>
  using mul1 = if_<size<>, mul<C>, always<number<1>, C>>;

  template<class C = identity>
  struct left_mul
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... * xs::value)>);
  };

  template<class C = identity>
  using left_mul0 = if_<size<>, left_mul<C>, always<number<0>, C>>;

  template<class C = identity>
  using left_mul1 = if_<size<>, left_mul<C>, always<number<1>, C>>;


  template<class C = identity>
  struct div
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... / xs::value)>);
  };

  template<class C = identity>
  using div0 = if_<size<>, div<C>, always<number<0>, C>>;

  template<class C = identity>
  using div1 = if_<size<>, div<C>, always<number<1>, C>>;

  template<class C = identity>
  struct mod
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... % xs::value)>);
  };

  template<class C = identity>
  using mod0 = if_<size<>, mod<C>, always<number<0>, C>>;

  template<class C = identity>
  using mod1 = if_<size<>, mod<C>, always<number<1>, C>>;


  template<class C = identity>
  struct xor_
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value ^ ...)>);
  };

  template<class C = identity>
  using xor0 = if_<size<>, xor_<C>, always<number<0>, C>>;

  template<class C = identity>
  struct left_xor
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... ^ xs::value)>);
  };

  template<class C = identity>
  using left_xor0 = if_<size<>, left_xor<C>, always<number<0>, C>>;


  template<class C = identity>
  struct bit_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value & ...)>);
  };

  template<class C = identity>
  using bit_and0 = if_<size<>, bit_and<C>, always<number<0>, C>>;

  template<class C = identity>
  struct left_bit_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... & xs::value)>);
  };

  template<class C = identity>
  using left_bit_and0 = if_<size<>, left_bit_and<C>, always<number<0>, C>>;


  template<class C = identity>
  struct bit_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value | ...)>);
  };

  template<class C = identity>
  using bit_or0 = if_<size<>, bit_or<C>, always<number<0>, C>>;

  template<class C = identity>
  struct left_bit_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... | xs::value)>);
  };

  template<class C = identity>
  using left_bit_or0 = if_<size<>, left_bit_or<C>, always<number<0>, C>>;


  template<class C = identity>
  struct neg
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(-x::value)>);
  };

  template<class C = identity>
  struct unary_plus
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(+x::value)>);
  };

  template<class C = identity>
  struct bit_not
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(~x::value)>);
  };

  template<class C = identity>
  struct inc
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value+1)>);
  };

  template<class C = identity>
  struct dec
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value-1)>);
  };

  template<class C = identity>
  struct equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value == y::value)>);
  };

  template<class C = identity>
  struct not_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value != y::value)>);
  };

  template<class C = identity>
  struct less
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value < y::value)>);
  };

  template<class C = identity>
  struct less_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value <= y::value)>);
  };

  template<class C = identity>
  struct greater
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value > y::value)>);
  };

  template<class C = identity>
  struct greater_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value >= y::value)>);
  };


  template<class N, class C = identity>
  using equal_to = push_front<N, equal<C>>;

  template<class N, class C = identity>
  using not_equal_to = push_front<N, not_equal<C>>;

  template<class N, class C = identity>
  using less_than = push_back<N, less<C>>;

  template<class N, class C = identity>
  using less_equal_than = push_back<N, less_equal<C>>;

  template<class N, class C = identity>
  using greater_than = push_back<N, greater<C>>;

  template<class N, class C = identity>
  using greater_equal_than = push_back<N, greater_equal<C>>;


  template<int_t n, class C = identity>
  using equal_to_c = equal_to<number<n>, C>;

  template<int_t n, class C = identity>
  using not_equal_to_c = not_equal_to<number<n>, C>;

  template<int_t n, class C = identity>
  using less_than_c = less_than<number<n>, C>;

  template<int_t n, class C = identity>
  using less_equal_than_c = less_equal_than<number<n>, C>;

  template<int_t n, class C = identity>
  using greater_than_c = greater_than<number<n>, C>;

  template<int_t n, class C = identity>
  using greater_equal_than_c = greater_equal_than<number<n>, C>;
}

namespace jln::mp::emp
{
  template<class L, class C = mp::identity>
  using or_seq = typename detail::_unpack<mp::or_<C>, L>::type;

  template<class L, class C = mp::identity>
  using and_seq = typename detail::_unpack<mp::and_<C>, L>::type;

  template<class L, class C = mp::identity>
  using or_left_seq = typename detail::_unpack<mp::left_or<C>, L>::type;

  template<class L, class C = mp::identity>
  using and_left_seq = typename detail::_unpack<mp::left_and<C>, L>::type;

  template<class L, class C = mp::identity>
  using add_seq = typename detail::_unpack<mp::add<C>, L>::type;

  template<class L, class C = mp::identity>
  using add0_seq = typename detail::_unpack<mp::add0<C>, L>::type;

  template<class L, class C = mp::identity>
  using left_add_seq = typename detail::_unpack<mp::left_add<C>, L>::type;

  template<class L, class C = mp::identity>
  using left_add0_seq = typename detail::_unpack<mp::left_add0<C>, L>::type;

  template<class L, class C = mp::identity>
  using sub_seq = typename detail::_unpack<mp::sub<C>, L>::type;

  template<class L, class C = mp::identity>
  using sub0_seq = typename detail::_unpack<mp::sub0<C>, L>::type;

  template<class L, class C = mp::identity>
  using lshift_seq = typename detail::_unpack<mp::lshift<C>, L>::type;

  template<class L, class C = mp::identity>
  using lshift0_seq = typename detail::_unpack<mp::lshift0<C>, L>::type;

  template<class L, class C = mp::identity>
  using rshift_seq = typename detail::_unpack<mp::rshift<C>, L>::type;

  template<class L, class C = mp::identity>
  using rshift0_seq = typename detail::_unpack<mp::rshift0<C>, L>::type;

  template<class L, class C = mp::identity>
  using mul_seq = typename detail::_unpack<mp::mul<C>, L>::type;

  template<class L, class C = mp::identity>
  using mul0_seq = typename detail::_unpack<mp::mul0<C>, L>::type;

  template<class L, class C = mp::identity>
  using mul1_seq = typename detail::_unpack<mp::mul1<C>, L>::type;

  template<class L, class C = mp::identity>
  using left_mul_seq = typename detail::_unpack<mp::left_mul<C>, L>::type;

  template<class L, class C = mp::identity>
  using left_mul0_seq = typename detail::_unpack<mp::left_mul0<C>, L>::type;

  template<class L, class C = mp::identity>
  using left_mul1_seq = typename detail::_unpack<mp::left_mul1<C>, L>::type;

  template<class L, class C = mp::identity>
  using div_seq = typename detail::_unpack<mp::div<C>, L>::type;

  template<class L, class C = mp::identity>
  using div0_seq = typename detail::_unpack<mp::div0<C>, L>::type;

  template<class L, class C = mp::identity>
  using div1_seq = typename detail::_unpack<mp::div1<C>, L>::type;

  template<class L, class C = mp::identity>
  using mod_seq = typename detail::_unpack<mp::mod<C>, L>::type;

  template<class L, class C = mp::identity>
  using mod0_seq = typename detail::_unpack<mp::mod0<C>, L>::type;

  template<class L, class C = mp::identity>
  using mod1_seq = typename detail::_unpack<mp::mod1<C>, L>::type;

  template<class L, class C = mp::identity>
  using xor_seq = typename detail::_unpack<mp::xor_<C>, L>::type;

  template<class L, class C = mp::identity>
  using xor0_seq = typename detail::_unpack<mp::xor0<C>, L>::type;

  template<class L, class C = mp::identity>
  using left_xor_seq = typename detail::_unpack<mp::left_xor<C>, L>::type;

  template<class L, class C = mp::identity>
  using left_xor0_seq = typename detail::_unpack<mp::left_xor0<C>, L>::type;

  template<class L, class C = mp::identity>
  using bit_and_seq = typename detail::_unpack<mp::bit_and<C>, L>::type;

  template<class L, class C = mp::identity>
  using bit_and0_seq = typename detail::_unpack<mp::bit_and0<C>, L>::type;

  template<class L, class C = mp::identity>
  using left_bit_and_seq = typename detail::_unpack<mp::left_bit_and<C>, L>::type;

  template<class L, class C = mp::identity>
  using left_bit_and0_seq = typename detail::_unpack<mp::left_bit_and0<C>, L>::type;

  template<class L, class C = mp::identity>
  using bit_or_seq = typename detail::_unpack<mp::bit_or<C>, L>::type;

  template<class L, class C = mp::identity>
  using bit_or0_seq = typename detail::_unpack<mp::bit_or0<C>, L>::type;

  template<class L, class C = mp::identity>
  using left_bit_or_seq = typename detail::_unpack<mp::left_bit_or<C>, L>::type;

  template<class L, class C = mp::identity>
  using left_bit_or0_seq = typename detail::_unpack<mp::left_bit_or0<C>, L>::type;


  template<int_t... xs>
  using or_c = number<(xs || ... || false)>;

  template<int_t... xs>
  using left_or_c = number<(false || ... || xs)>;

  template<int_t... xs>
  using and_c = number<(xs && ... && true)>;

  template<int_t... xs>
  using left_and_c = number<(true && ... && xs)>;

  template<int_t... xs>
  using add_c = number<(xs + ...)>;

  template<int_t... xs>
  using add0_c = add_c<xs..., 0>;

  template<int_t... xs>
  using left_add_c = number<(... + xs)>;

  template<int_t... xs>
  using left_add0_c = left_add_c<xs..., 0>;

  template<int_t... xs>
  using sub_c = number<(... - xs)>;

  template<int_t... xs>
  using sub0_c = sub_c<xs..., 0>;

  template<int_t... xs>
  using lshift_c = number<(... << xs)>;

  template<int_t... xs>
  using lshift0_c = lshift_c<xs..., 0>;

  template<int_t... xs>
  using rshift_c = number<(... >> xs)>;

  template<int_t... xs>
  using rshift0_c = rshift_c<xs..., 0>;

  template<int_t... xs>
  using mul_c = number<(xs * ...)>;

  template<int_t... xs>
  using mul0_c = mul_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<int_t... xs>
  using mul1_c = mul_c<xs..., 1>;

  template<int_t... xs>
  using left_mul_c = number<(... * xs)>;

  template<int_t... xs>
  using left_mul0_c = left_mul_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<int_t... xs>
  using left_mul1_c = left_mul_c<xs..., 1>;

  template<int_t... xs>
  using div_c = number<(... / xs)>;

  template<int_t... xs>
  using div0_c = div_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<int_t... xs>
  using div1_c = div_c<xs..., 1>;

  template<int_t... xs>
  using mod_c = number<(... % xs)>;

  template<int_t... xs>
  using mod0_c = mod_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_t>::min() : 0)>;

  template<int_t... xs>
  using mod1_c = mod_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_t>::min() : 1)>;

  template<int_t... xs>
  using xor_c = number<(xs ^ ...)>;

  template<int_t... xs>
  using xor0_c = xor_c<xs..., 0, 0>;

  template<int_t... xs>
  using left_xor_c = number<(... ^ xs)>;

  template<int_t... xs>
  using left_xor0_c = left_xor_c<xs..., 0, 0>;

  template<int_t... xs>
  using bit_and_c = number<(xs & ...)>;

  template<int_t... xs>
  using bit_and0_c = bit_and_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_t>::max() : 0)>;

  template<int_t... xs>
  using left_bit_and_c = number<(... & xs)>;

  template<int_t... xs>
  using left_bit_and0_c = left_bit_and_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_t>::max() : 0)>;

  template<int_t... xs>
  using bit_or_c = number<(xs | ...)>;

  template<int_t... xs>
  using bit_or0_c = bit_or_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_t>::max() : 0)>;

  template<int_t... xs>
  using left_bit_or_c = number<(... | xs)>;

  template<int_t... xs>
  using left_bit_or0_c = left_bit_or_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_t>::max() : 0)>;


  template<class... xs>
  using or_ = number<(xs::value || ... || false)>;

  template<class... xs>
  using and_ = number<(xs::value && ... && true)>;

  template<class... xs>
  using left_or = number<(false || ... || xs::value)>;

  template<class... xs>
  using left_and = number<(true && ... && xs::value)>;

  template<class... xs>
  using add = number<(xs::value + ...)>;

  template<class... xs>
  using add0 = typename mp::add0<>::template f<xs...>;

  template<class... xs>
  using left_add = number<(... + xs::value)>;

  template<class... xs>
  using left_add0 = typename mp::add0<>::template f<xs...>;

  template<class... xs>
  using sub = number<(... - xs::value)>;

  template<class... xs>
  using sub0 = typename mp::sub0<>::template f<xs...>;

  template<class... xs>
  using lshift = number<(... << xs::value)>;

  template<class... xs>
  using lshift0 = typename mp::lshift0<>::template f<xs...>;

  template<class... xs>
  using rshift = number<(... >> xs::value)>;

  template<class... xs>
  using rshift0 = typename mp::rshift0<>::template f<xs...>;

  template<class... xs>
  using mul = number<(xs::value * ...)>;

  template<class... xs>
  using mul0 = typename mp::mul0<>::template f<xs...>;

  template<class... xs>
  using mul1 = typename mp::mul1<>::template f<xs...>;

  template<class... xs>
  using left_mul = number<(... * xs::value)>;

  template<class... xs>
  using left_mul0 = typename mp::left_mul0<>::template f<xs...>;

  template<class... xs>
  using left_mul1 = typename mp::left_mul1<>::template f<xs...>;

  template<class... xs>
  using div = number<(... / xs::value)>;

  template<class... xs>
  using div0 = typename mp::div0<>::template f<xs...>;

  template<class... xs>
  using div1 = typename mp::div1<>::template f<xs...>;

  template<class... xs>
  using mod = number<(... % xs::value)>;

  template<class... xs>
  using mod0 = typename mp::mod0<>::template f<xs...>;

  template<class... xs>
  using mod1 = typename mp::mod1<>::template f<xs...>;

  template<class... xs>
  using xor_ = number<(xs::value ^ ...)>;

  template<class... xs>
  using xor0 = typename mp::xor0<>::template f<xs...>;

  template<class... xs>
  using left_xor = number<(... ^ xs::value)>;

  template<class... xs>
  using left_xor0 = typename mp::left_xor0<>::template f<xs...>;

  template<class... xs>
  using bit_and = number<(xs::value & ...)>;

  template<class... xs>
  using bit_and0 = typename mp::bit_and0<>::template f<xs...>;

  template<class... xs>
  using left_bit_and = number<(... & xs::value)>;

  template<class... xs>
  using left_bit_and0 = typename mp::left_bit_and0<>::template f<xs...>;

  template<class... xs>
  using bit_or = number<(xs::value | ...)>;

  template<class... xs>
  using bit_or0 = typename mp::bit_or0<>::template f<xs...>;

  template<class... xs>
  using left_bit_or = number<(... | xs::value)>;

  template<class... xs>
  using left_bit_or0 = typename mp::left_bit_or0<>::template f<xs...>;


  template<class x, class C = mp::identity>
  using neg = typename mp::neg<C>::template f<x>;

  template<class x, class C = mp::identity>
  using unary_plus = typename mp::unary_plus<C>::template f<x>;

  template<class x, class C = mp::identity>
  using bit_not = typename mp::bit_not<C>::template f<x>;

  template<class x, class C = mp::identity>
  using inc = typename mp::inc<C>::template f<x>;

  template<class x, class C = mp::identity>
  using dec = typename mp::dec<C>::template f<x>;

  template<class x, class y, class C = mp::identity>
  using equal = typename mp::equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using not_equal = typename mp::not_equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using less = typename mp::less<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using less_equal = typename mp::less_equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using greater = typename mp::greater<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using greater_equal = typename mp::greater_equal<C>::template f<x, y>;


  template<class L, class C = mp::identity>
  inline constexpr int_t or_seq_v = detail::_unpack<mp::or_<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t and_seq_v = detail::_unpack<mp::and_<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t or_left_seq_v = detail::_unpack<mp::left_or<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t and_left_seq_v = detail::_unpack<mp::left_and<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t add_seq_v = detail::_unpack<mp::add<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t add0_seq_v = detail::_unpack<mp::add0<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t left_add_seq_v = detail::_unpack<mp::left_add<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t left_add0_seq_v = detail::_unpack<mp::left_add0<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t sub_seq_v = detail::_unpack<mp::sub<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t sub0_seq_v = detail::_unpack<mp::sub0<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t lshift_seq_v = detail::_unpack<mp::lshift<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t lshift0_seq_v = detail::_unpack<mp::lshift0<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t rshift_seq_v = detail::_unpack<mp::rshift<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t rshift0_seq_v = detail::_unpack<mp::rshift0<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t mul_seq_v = detail::_unpack<mp::mul<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t mul0_seq_v = detail::_unpack<mp::mul0<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t mul1_seq_v = detail::_unpack<mp::mul1<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t left_mul_seq_v = detail::_unpack<mp::left_mul<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t left_mul0_seq_v = detail::_unpack<mp::left_mul0<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t left_mul1_seq_v = detail::_unpack<mp::left_mul1<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t div_seq_v = detail::_unpack<mp::div<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t div0_seq_v = detail::_unpack<mp::div0<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t div1_seq_v = detail::_unpack<mp::div1<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t mod_seq_v = detail::_unpack<mp::mod<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t mod0_seq_v = detail::_unpack<mp::mod0<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t mod1_seq_v = detail::_unpack<mp::mod1<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t xor_seq_v = detail::_unpack<mp::xor_<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t xor0_seq_v = detail::_unpack<mp::xor0<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t left_xor_seq_v = detail::_unpack<mp::left_xor<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t left_xor0_seq_v = detail::_unpack<mp::left_xor0<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t bit_and_seq_v = detail::_unpack<mp::bit_and<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t bit_and0_seq_v = detail::_unpack<mp::bit_and0<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t left_bit_and_seq_v = detail::_unpack<mp::left_bit_and<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t left_bit_and0_seq_v = detail::_unpack<mp::left_bit_and0<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t bit_or_seq_v = detail::_unpack<mp::bit_or<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t bit_or0_seq_v = detail::_unpack<mp::bit_or0<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t left_bit_or_seq_v = detail::_unpack<mp::left_bit_or<C>, L>::type::value;

  template<class L, class C = mp::identity>
  inline constexpr int_t left_bit_or0_seq_v = detail::_unpack<mp::left_bit_or0<C>, L>::type::value;


  template<int_t... xs>
  inline constexpr int_t or_c_v = (xs || ... || false);

  template<int_t... xs>
  inline constexpr int_t left_or_c_v = (false || ... || xs);

  template<int_t... xs>
  inline constexpr int_t and_c_v = (xs && ... && true);

  template<int_t... xs>
  inline constexpr int_t left_and_c_v = (true && ... && xs);

  template<int_t... xs>
  inline constexpr int_t add_c_v = (xs + ...);

  template<int_t... xs>
  inline constexpr int_t add0_c_v = add_c_v<xs..., 0>;

  template<int_t... xs>
  inline constexpr int_t left_add_c_v = (... + xs);

  template<int_t... xs>
  inline constexpr int_t left_add0_c_v = left_add_c_v<xs..., 0>;

  template<int_t... xs>
  inline constexpr int_t sub_c_v = (... - xs);

  template<int_t... xs>
  inline constexpr int_t sub0_c_v = sub_c_v<xs..., 0>;

  template<int_t... xs>
  inline constexpr int_t lshift_c_v = (... << xs);

  template<int_t... xs>
  inline constexpr int_t lshift0_c_v = lshift_c_v<xs..., 0>;

  template<int_t... xs>
  inline constexpr int_t rshift_c_v = (... >> xs);

  template<int_t... xs>
  inline constexpr int_t rshift0_c_v = rshift_c_v<xs..., 0>;

  template<int_t... xs>
  inline constexpr int_t mul_c_v = (xs * ...);

  template<int_t... xs>
  inline constexpr int_t mul0_c_v = mul_c_v<xs..., sizeof...(xs) ? 1 : 0>;

  template<int_t... xs>
  inline constexpr int_t mul1_c_v = mul_c_v<xs..., 1>;

  template<int_t... xs>
  inline constexpr int_t left_mul_c_v = (... * xs);

  template<int_t... xs>
  inline constexpr int_t left_mul0_c_v = left_mul_c_v<xs..., sizeof...(xs) ? 1 : 0>;

  template<int_t... xs>
  inline constexpr int_t left_mul1_c_v = left_mul_c_v<xs..., 1>;

  template<int_t... xs>
  inline constexpr int_t div_c_v = (... / xs);

  template<int_t... xs>
  inline constexpr int_t div0_c_v = div_c_v<xs..., sizeof...(xs) ? 1 : 0>;

  template<int_t... xs>
  inline constexpr int_t div1_c_v = div_c_v<xs..., 1>;

  template<int_t... xs>
  inline constexpr int_t mod_c_v = (... % xs);

  template<int_t... xs>
  inline constexpr int_t mod0_c_v = mod_c_v<xs...,
    sizeof...(xs) ? std::numeric_limits<int_t>::min() : 0>;

  template<int_t... xs>
  inline constexpr int_t mod1_c_v = mod_c_v<xs...,
    sizeof...(xs) ? std::numeric_limits<int_t>::min() : 1>;

  template<int_t... xs>
  inline constexpr int_t xor_c_v = (xs ^ ...);

  template<int_t... xs>
  inline constexpr int_t xor0_c_v = xor_c_v<xs..., 0, 0>;

  template<int_t... xs>
  inline constexpr int_t left_xor_c_v = (... ^ xs);

  template<int_t... xs>
  inline constexpr int_t left_xor0_c_v = left_xor_c_v<xs..., 0, 0>;

  template<int_t... xs>
  inline constexpr int_t bit_and_c_v = (xs & ...);

  template<int_t... xs>
  inline constexpr int_t bit_and0_c_v = bit_and_c_v<xs...,
    sizeof...(xs) ? std::numeric_limits<int_t>::max() : 0>;

  template<int_t... xs>
  inline constexpr int_t left_bit_and_c_v = (... & xs);

  template<int_t... xs>
  inline constexpr int_t left_bit_and0_c_v = left_bit_and_c_v<xs...,
    sizeof...(xs) ? std::numeric_limits<int_t>::max() : 0>;

  template<int_t... xs>
  inline constexpr int_t bit_or_c_v = (xs | ...);

  template<int_t... xs>
  inline constexpr int_t bit_or0_c_v = bit_or_c_v<xs...,
    sizeof...(xs) ? std::numeric_limits<int_t>::max() : 0>;

  template<int_t... xs>
  inline constexpr int_t left_bit_or_c_v = (... | xs);

  template<int_t... xs>
  inline constexpr int_t left_bit_or0_c_v = left_bit_or_c_v<xs...,
    sizeof...(xs) ? std::numeric_limits<int_t>::max() : 0>;


  template<class... xs>
  inline constexpr int_t or_v = (xs::value || ... || false);

  template<class... xs>
  inline constexpr int_t and_v = (xs::value && ... && true);

  template<class... xs>
  inline constexpr int_t left_or_v = (false || ... || xs::value);

  template<class... xs>
  inline constexpr int_t left_and_v = (true && ... && xs::value);

  template<class... xs>
  inline constexpr int_t add_v = (xs::value + ...);

  template<class... xs>
  inline constexpr int_t add0_v = mp::add0<>::template f<xs...>::value;

  template<class... xs>
  inline constexpr int_t left_add_v = (... + xs::value);

  template<class... xs>
  inline constexpr int_t left_add0_v = mp::add0<>::template f<xs...>::value;

  template<class... xs>
  inline constexpr int_t sub_v = (... - xs::value);

  template<class... xs>
  inline constexpr int_t sub0_v = mp::sub0<>::template f<xs...>::value;

  template<class... xs>
  inline constexpr int_t lshift_v = (... << xs::value);

  template<class... xs>
  inline constexpr int_t lshift0_v = mp::lshift0<>::template f<xs...>::value;

  template<class... xs>
  inline constexpr int_t rshift_v = (... >> xs::value);

  template<class... xs>
  inline constexpr int_t rshift0_v = mp::rshift0<>::template f<xs...>::value;

  template<class... xs>
  inline constexpr int_t mul_v = (xs::value * ...);

  template<class... xs>
  inline constexpr int_t mul0_v = mp::mul0<>::template f<xs...>::value;

  template<class... xs>
  inline constexpr int_t mul1_v = mp::mul1<>::template f<xs...>::value;

  template<class... xs>
  inline constexpr int_t left_mul_v = (... * xs::value);

  template<class... xs>
  inline constexpr int_t left_mul0_v = mp::left_mul0<>::template f<xs...>::value;

  template<class... xs>
  inline constexpr int_t left_mul1_v = mp::left_mul1<>::template f<xs...>::value;

  template<class... xs>
  inline constexpr int_t div_v = (... / xs::value);

  template<class... xs>
  inline constexpr int_t div0_v = mp::div0<>::template f<xs...>::value;

  template<class... xs>
  inline constexpr int_t div1_v = mp::div1<>::template f<xs...>::value;

  template<class... xs>
  inline constexpr int_t mod_v = (... % xs::value);

  template<class... xs>
  inline constexpr int_t mod0_v = mp::mod0<>::template f<xs...>::value;

  template<class... xs>
  inline constexpr int_t mod1_v = mp::mod1<>::template f<xs...>::value;

  template<class... xs>
  inline constexpr int_t xor_v = (xs::value ^ ...);

  template<class... xs>
  inline constexpr int_t xor0_v = mp::xor0<>::template f<xs...>::value;

  template<class... xs>
  inline constexpr int_t left_xor_v = (... ^ xs::value);

  template<class... xs>
  inline constexpr int_t left_xor0_v = mp::left_xor0<>::template f<xs...>::value;

  template<class... xs>
  inline constexpr int_t bit_and_v = (xs::value & ...);

  template<class... xs>
  inline constexpr int_t bit_and0_v = mp::bit_and0<>::template f<xs...>::value;

  template<class... xs>
  inline constexpr int_t left_bit_and_v = (... & xs::value);

  template<class... xs>
  inline constexpr int_t left_bit_and0_v = mp::left_bit_and0<>::template f<xs...>::value;

  template<class... xs>
  inline constexpr int_t bit_or_v = (xs::value | ...);

  template<class... xs>
  inline constexpr int_t bit_or0_v = mp::bit_or0<>::template f<xs...>::value;

  template<class... xs>
  inline constexpr int_t left_bit_or_v = (... | xs::value);

  template<class... xs>
  inline constexpr int_t left_bit_or0_v = mp::left_bit_or0<>::template f<xs...>::value;


  template<class x, class C = mp::identity>
  inline constexpr int_t neg_v = mp::neg<C>::template f<x>;

  template<class x, class C = mp::identity>
  inline constexpr int_t unary_plus_v = mp::unary_plus<C>::template f<x>;

  template<class x, class C = mp::identity>
  inline constexpr int_t bit_not_v = mp::bit_not<C>::template f<x>;

  template<class x, class C = mp::identity>
  inline constexpr int_t inc_v = mp::inc<C>::template f<x>;

  template<class x, class C = mp::identity>
  inline constexpr int_t dec_v = mp::dec<C>::template f<x>;

  template<class x, class y, class C = mp::identity>
  inline constexpr int_t equal_v = mp::equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  inline constexpr int_t not_equal_v = mp::not_equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  inline constexpr int_t less_v = mp::less<C>::template f<x, y::value>;

  template<class x, class y, class C = mp::identity>
  inline constexpr int_t less_equal_v = mp::less_equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  inline constexpr int_t greater_v = mp::greater<C>::template f<x, y::value>;

  template<class x, class y, class C = mp::identity>
  inline constexpr int_t greater_equal_v = mp::greater_equal<C>::template f<x, y>;
}

JLN_MP_DIAGNOSTIC_POP()


#include <jln/mp/number/as_bool.hpp>
#include <jln/mp/number/to_bool.hpp>

/// \cond
namespace jln::mp
{
  template<>
  struct or_<identity>
  {
    template<class... xs>
    using f = number<(xs::value || ... || false)>;
  };

  template<>
  struct left_or<identity>
  {
    template<class... xs>
    using f = number<(false || ... || xs::value)>;
  };


  template<>
  struct and_<identity>
  {
    template<class... xs>
    using f = number<(xs::value && ... && true)>;
  };

  template<>
  struct left_and<identity>
  {
    template<class... xs>
    using f = number<(true && ... && xs::value)>;
  };


  template<>
  struct add<identity>
  {
    template<class... xs>
    using f = number<(xs::value + ...)>;
  };

  template<>
  struct left_add<identity>
  {
    template<class... xs>
    using f = number<(... + xs::value)>;
  };


  template<>
  struct equal<identity>
  {
    template<class x, class y>
    using f = number<(x::value == y::value)>;
  };

  template<>
  struct not_equal<identity>
  {
    template<class x, class y>
    using f = number<(x::value != y::value)>;
  };

  template<>
  struct less<identity>
  {
    template<class x, class y>
    using f = number<(x::value < y::value)>;
  };

  template<>
  struct less_equal<identity>
  {
    template<class x, class y>
    using f = number<(x::value <= y::value)>;
  };

  template<>
  struct greater<identity>
  {
    template<class x, class y>
    using f = number<(x::value > y::value)>;
  };

  template<>
  struct greater_equal<identity>
  {
    template<class x, class y>
    using f = number<(x::value >= y::value)>;
  };
}
/// \endcond
