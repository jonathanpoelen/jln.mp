#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/list/push_front.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/number/number.hpp>
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
  struct not_
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(!x::value)>);
  };

  template<class C>
  struct not_<not_<C>>
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(!int_{!x::value})>);
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


  template<int_ n, class C = identity>
  using equal_to_c = equal_to<number<n>, C>;

  template<int_ n, class C = identity>
  using not_equal_to_c = not_equal_to<number<n>, C>;

  template<int_ n, class C = identity>
  using less_than_c = less_than<number<n>, C>;

  template<int_ n, class C = identity>
  using less_equal_than_c = less_equal_than<number<n>, C>;

  template<int_ n, class C = identity>
  using greater_than_c = greater_than<number<n>, C>;

  template<int_ n, class C = identity>
  using greater_equal_than_c = greater_equal_than<number<n>, C>;
}

namespace jln::mp::emp
{
  template<class L, class C = mp::identity>
  using or_seq = unpack<L, mp::or_<C>>;

  template<class L, class C = mp::identity>
  using and_seq = unpack<L, mp::and_<C>>;

  template<class L, class C = mp::identity>
  using or_left_seq = unpack<L, mp::left_or<C>>;

  template<class L, class C = mp::identity>
  using and_left_seq = unpack<L, mp::left_and<C>>;

  template<class L, class C = mp::identity>
  using add_seq = unpack<L, mp::add<C>>;

  template<class L, class C = mp::identity>
  using add0_seq = unpack<L, mp::add0<C>>;

  template<class L, class C = mp::identity>
  using left_add_seq = unpack<L, mp::left_add<C>>;

  template<class L, class C = mp::identity>
  using left_add0_seq = unpack<L, mp::left_add0<C>>;

  template<class L, class C = mp::identity>
  using sub_seq = unpack<L, mp::sub<C>>;

  template<class L, class C = mp::identity>
  using sub0_seq = unpack<L, mp::sub0<C>>;

  template<class L, class C = mp::identity>
  using lshift_seq = unpack<L, mp::lshift<C>>;

  template<class L, class C = mp::identity>
  using lshift0_seq = unpack<L, mp::lshift0<C>>;

  template<class L, class C = mp::identity>
  using rshift_seq = unpack<L, mp::rshift<C>>;

  template<class L, class C = mp::identity>
  using rshift0_seq = unpack<L, mp::rshift0<C>>;

  template<class L, class C = mp::identity>
  using mul_seq = unpack<L, mp::mul<C>>;

  template<class L, class C = mp::identity>
  using mul0_seq = unpack<L, mp::mul0<C>>;

  template<class L, class C = mp::identity>
  using mul1_seq = unpack<L, mp::mul1<C>>;

  template<class L, class C = mp::identity>
  using left_mul_seq = unpack<L, mp::left_mul<C>>;

  template<class L, class C = mp::identity>
  using left_mul0_seq = unpack<L, mp::left_mul0<C>>;

  template<class L, class C = mp::identity>
  using left_mul1_seq = unpack<L, mp::left_mul1<C>>;

  template<class L, class C = mp::identity>
  using div_seq = unpack<L, mp::div<C>>;

  template<class L, class C = mp::identity>
  using div0_seq = unpack<L, mp::div0<C>>;

  template<class L, class C = mp::identity>
  using div1_seq = unpack<L, mp::div1<C>>;

  template<class L, class C = mp::identity>
  using mod_seq = unpack<L, mp::mod<C>>;

  template<class L, class C = mp::identity>
  using mod0_seq = unpack<L, mp::mod0<C>>;

  template<class L, class C = mp::identity>
  using mod1_seq = unpack<L, mp::mod1<C>>;

  template<class L, class C = mp::identity>
  using xor_seq = unpack<L, mp::xor_<C>>;

  template<class L, class C = mp::identity>
  using xor0_seq = unpack<L, mp::xor0<C>>;

  template<class L, class C = mp::identity>
  using left_xor_seq = unpack<L, mp::left_xor<C>>;

  template<class L, class C = mp::identity>
  using left_xor0_seq = unpack<L, mp::left_xor0<C>>;

  template<class L, class C = mp::identity>
  using bit_and_seq = unpack<L, mp::bit_and<C>>;

  template<class L, class C = mp::identity>
  using bit_and0_seq = unpack<L, mp::bit_and0<C>>;

  template<class L, class C = mp::identity>
  using left_bit_and_seq = unpack<L, mp::left_bit_and<C>>;

  template<class L, class C = mp::identity>
  using left_bit_and0_seq = unpack<L, mp::left_bit_and0<C>>;

  template<class L, class C = mp::identity>
  using bit_or_seq = unpack<L, mp::bit_or<C>>;

  template<class L, class C = mp::identity>
  using bit_or0_seq = unpack<L, mp::bit_or0<C>>;

  template<class L, class C = mp::identity>
  using left_bit_or_seq = unpack<L, mp::left_bit_or<C>>;

  template<class L, class C = mp::identity>
  using left_bit_or0_seq = unpack<L, mp::left_bit_or0<C>>;


  template<int_... xs>
  using or_c = number<(xs || ... || false)>;

  template<int_... xs>
  using left_or_c = number<(false || ... || xs)>;

  template<int_... xs>
  using and_c = number<(xs && ... && true)>;

  template<int_... xs>
  using left_and_c = number<(true && ... && xs)>;

  template<int_... xs>
  using add_c = number<(xs + ...)>;

  template<int_... xs>
  using add0_c = add_c<xs..., 0>;

  template<int_... xs>
  using left_add_c = number<(... + xs)>;

  template<int_... xs>
  using left_add0_c = left_add_c<xs..., 0>;

  template<int_... xs>
  using sub_c = number<(... - xs)>;

  template<int_... xs>
  using sub0_c = sub_c<xs..., 0>;

  template<int_... xs>
  using lshift_c = number<(... << xs)>;

  template<int_... xs>
  using lshift0_c = lshift_c<xs..., 0>;

  template<int_... xs>
  using rshift_c = number<(... >> xs)>;

  template<int_... xs>
  using rshift0_c = rshift_c<xs..., 0>;

  template<int_... xs>
  using mul_c = number<(xs * ...)>;

  template<int_... xs>
  using mul0_c = mul_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<int_... xs>
  using mul1_c = mul_c<xs..., 1>;

  template<int_... xs>
  using left_mul_c = number<(... * xs)>;

  template<int_... xs>
  using left_mul0_c = left_mul_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<int_... xs>
  using left_mul1_c = left_mul_c<xs..., 1>;

  template<int_... xs>
  using div_c = number<(... / xs)>;

  template<int_... xs>
  using div0_c = div_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<int_... xs>
  using div1_c = div_c<xs..., 1>;

  template<int_... xs>
  using mod_c = number<(... % xs)>;

  template<int_... xs>
  using mod0_c = mod_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::min() : 0)>;

  template<int_... xs>
  using mod1_c = mod_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::min() : 1)>;

  template<int_... xs>
  using xor_c = number<(xs ^ ...)>;

  template<int_... xs>
  using xor0_c = xor_c<xs..., 0, 0>;

  template<int_... xs>
  using left_xor_c = number<(... ^ xs)>;

  template<int_... xs>
  using left_xor0_c = left_xor_c<xs..., 0, 0>;

  template<int_... xs>
  using bit_and_c = number<(xs & ...)>;

  template<int_... xs>
  using bit_and0_c = bit_and_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::max() : 0)>;

  template<int_... xs>
  using left_bit_and_c = number<(... & xs)>;

  template<int_... xs>
  using left_bit_and0_c = left_bit_and_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::max() : 0)>;

  template<int_... xs>
  using bit_or_c = number<(xs | ...)>;

  template<int_... xs>
  using bit_or0_c = bit_or_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::max() : 0)>;

  template<int_... xs>
  using left_bit_or_c = number<(... | xs)>;

  template<int_... xs>
  using left_bit_or0_c = left_bit_or_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::max() : 0)>;


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
  using not_ = typename mp::not_<C>::template f<x>;

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
}

JLN_MP_DIAGNOSTIC_POP()

/// \cond
#include <jln/mp/number/as_bool.hpp>
#include <jln/mp/number/to_bool.hpp>

namespace jln::mp
{
  template<>
  struct as_bool<not_<>>
  {
    template<class x>
    using f = number<!bool{x::value}>;
  };

  template<class C>
  struct as_bool<not_<C>>
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<!bool{x::value}>);
  };

  template<>
  struct to_bool<not_<>>
  {
    template<class x>
    using f = number<!bool(x::value)>;
  };

  template<class C>
  struct to_bool<not_<C>>
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<!bool(x::value)>);
  };

  template<class TC, class FC>
  struct if_<size<not_<>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<!sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
      ::template f<xs...>;
  };
}

/// \endcond
