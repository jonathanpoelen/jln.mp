#pragma once

#include "../functional/identity.hpp"
#include "../functional/if.hpp"
#include "../list/push_back.hpp"
#include "../list/size.hpp"
#include "../number/number.hpp"
#include "../utility/always.hpp"
#include "../utility/unpack.hpp"

#include "../../cxx/diagnostic.hpp"

#include <limits>

JLN_DIAGNOSTIC_PUSH
JLN_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wlogical-op")

namespace jln::mp
{
  template<class C = identity>
  struct or_
  {
    template<class... xs>
    using f = typename C::template f<number<(false || ... || xs::value)>>;
  };

  template<class C = identity>
  struct and_
  {
    template<class... xs>
    using f = typename C::template f<number<(true && ... && xs::value)>>;
  };

  template<class C = identity>
  struct add
  {
    template<class... xs>
    using f = typename C::template f<number<(... + xs::value)>>;
  };

  template<class C = identity>
  using add0 = if_<size<>, add<C>, always<number<0>, C>>;

  template<class C = identity>
  struct sub
  {
    template<class... xs>
    using f = typename C::template f<number<(... - xs::value)>>;
  };

  template<class C = identity>
  using sub0 = if_<size<>, sub<C>, always<number<0>, C>>;

  template<class C = identity>
  struct lshift
  {
    template<class... xs>
    using f = typename C::template f<number<(... << xs::value)>>;
  };

  template<class C = identity>
  using lshift0 = if_<size<>, lshift<C>, always<number<0>, C>>;

  template<class C = identity>
  struct rshift
  {
    template<class... xs>
    using f = typename C::template f<number<(... >> xs::value)>>;
  };

  template<class C = identity>
  using rshift0 = if_<size<>, rshift<C>, always<number<0>, C>>;

  template<class C = identity>
  struct mul
  {
    template<class... xs>
    using f = typename C::template f<number<(... * xs::value)>>;
  };

  template<class C = identity>
  using mul0 = if_<size<>, mul<C>, always<number<0>, C>>;

  template<class C = identity>
  using mul1 = if_<size<>, mul<C>, always<number<1>, C>>;

  template<class C = identity>
  struct div
  {
    template<class... xs>
    using f = typename C::template f<number<(... / xs::value)>>;
  };

  template<class C = identity>
  using div0 = if_<size<>, div<C>, always<number<0>, C>>;

  template<class C = identity>
  using div1 = if_<size<>, div<C>, always<number<1>, C>>;

  template<class C = identity>
  struct mod
  {
    template<class... xs>
    using f = typename C::template f<number<(... %  xs::value)>>;
  };

  template<class C = identity>
  using mod0 = if_<size<>, mod<C>, always<number<0>, C>>;

  template<class C = identity>
  using mod1 = if_<size<>, mod<C>, always<number<1>, C>>;

  template<class C = identity>
  struct xor_
  {
    template<class... xs>
    using f = typename C::template f<number<(... ^ xs::value)>>;
  };

  template<class C = identity>
  using xor0 = if_<size<>, xor_<C>, always<number<0>, C>>;

  template<class C = identity>
  struct bit_and
  {
    template<class... xs>
    using f = typename C::template f<number<(... & xs::value)>>;
  };

  template<class C = identity>
  using bit_and0 = if_<size<>, bit_and<C>, always<number<0>, C>>;

  template<class C = identity>
  struct bit_or
  {
    template<class... xs>
    using f = typename C::template f<number<(... | xs::value)>>;
  };

  template<class C = identity>
  using bit_or0 = if_<size<>, bit_or<C>, always<number<0>, C>>;

  template<class C = identity>
  struct neg
  {
    template<class x>
    using f = typename C::template f<number<(-x::value)>>;
  };

  template<class C = identity>
  struct unary_plus
  {
    template<class x>
    using f = typename C::template f<number<(+x::value)>>;
  };

  template<class C = identity>
  struct not_
  {
    template<class x>
    using f = typename C::template f<number<(!x::value)>>;
  };

  template<class C = identity>
  struct bit_not
  {
    template<class x>
    using f = typename C::template f<number<(~x::value)>>;
  };

  template<class C = identity>
  struct inc
  {
    template<class x>
    using f = typename C::template f<number<(x::value+1)>>;
  };

  template<class C = identity>
  struct dec
  {
    template<class x>
    using f = typename C::template f<number<(x::value-1)>>;
  };

  template<class C = identity>
  struct equal
  {
    template<class x, class y>
    using f = typename C::template f<number<(x::value == y::value)>>;
  };

  template<class C = identity>
  struct not_equal
  {
    template<class x, class y>
    using f = typename C::template f<number<(x::value != y::value)>>;
  };

  template<class C = identity>
  struct less
  {
    template<class x, class y>
    using f = typename C::template f<number<(x::value < y::value)>>;
  };

  template<class C = identity>
  struct less_equal
  {
    template<class x, class y>
    using f = typename C::template f<number<(x::value <= y::value)>>;
  };

  template<class C = identity>
  struct greater
  {
    template<class x, class y>
    using f = typename C::template f<number<(x::value > y::value)>>;
  };

  template<class C = identity>
  struct greater_equal
  {
    template<class x, class y>
    using f = typename C::template f<number<(x::value >= y::value)>>;
  };


  template<class N, class C = identity>
  using equal_than = push_back<N, equal<C>>;

  template<class N, class C = identity>
  using not_equal_than = push_back<N, not_equal<C>>;

  template<class N, class C = identity>
  using less_than = push_back<N, less<C>>;

  template<class N, class C = identity>
  using less_equal_than = push_back<N, less_equal<C>>;

  template<class N, class C = identity>
  using greater_than = push_back<N, greater<C>>;

  template<class N, class C = identity>
  using greater_equal_than = push_back<N, greater_equal<C>>;


  template<int_ n, class C = identity>
  using equal_than_c = equal_than<number<n>, C>;

  template<int_ n, class C = identity>
  using not_equal_than_c = not_equal_than<number<n>, C>;

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
  using add_seq = unpack<L, mp::add<C>>;

  template<class L, class C = mp::identity>
  using add0_seq = unpack<L, mp::add0<C>>;

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
  using bit_and_seq = unpack<L, mp::bit_and<C>>;

  template<class L, class C = mp::identity>
  using bit_and0_seq = unpack<L, mp::bit_and0<C>>;

  template<class L, class C = mp::identity>
  using bit_or_seq = unpack<L, mp::bit_or<C>>;

  template<class L, class C = mp::identity>
  using bit_or0_seq = unpack<L, mp::bit_or0<C>>;


  template<int_... xs>
  using or_c = number<(false || ... || xs)>;

  template<int_... xs>
  using and_c = number<(true && ... && xs)>;

  template<int_... xs>
  using add_c = number<(... + xs)>;

  template<int_... xs>
  using add0_c = add_c<xs..., 0>;

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
  using mul_c = number<(... * xs)>;

  template<int_... xs>
  using mul0_c = mul_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<int_... xs>
  using mul1_c = mul_c<xs..., 1>;

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
  using xor_c = number<(... ^ xs)>;

  template<int_... xs>
  using xor0_c = xor_c<xs..., 0, 0>;

  template<int_... xs>
  using bit_and_c = number<(... & xs)>;

  template<int_... xs>
  using bit_and0_c = bit_and_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::max() : 0)>;

  template<int_... xs>
  using bit_or_c = number<(... | xs)>;

  template<int_... xs>
  using bit_or0_c = bit_or_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::max() : 0)>;


  template<class... xs>
  using or_ = number<(false || ... || xs::value)>;

  template<class... xs>
  using and_ = number<(true && ... && xs::value)>;

  template<class... xs>
  using add = number<(... + xs::value)>;

  template<class... xs>
  using add0 = call<mp::add0<>, xs...>;

  template<class... xs>
  using sub = number<(... - xs::value)>;

  template<class... xs>
  using sub0 = call<mp::sub0<>, xs...>;

  template<class... xs>
  using lshift = number<(... << xs::value)>;

  template<class... xs>
  using lshift0 = call<mp::lshift0<>, xs...>;

  template<class... xs>
  using rshift = number<(... >> xs::value)>;

  template<class... xs>
  using rshift0 = call<mp::rshift0<>, xs...>;

  template<class... xs>
  using mul = number<(... * xs::value)>;

  template<class... xs>
  using mul0 = call<mp::mul0<>, xs...>;

  template<class... xs>
  using mul1 = call<mp::mul1<>, xs...>;

  template<class... xs>
  using div = number<(... / xs::value)>;

  template<class... xs>
  using div0 = call<mp::div0<>, xs...>;

  template<class... xs>
  using div1 = call<mp::div1<>, xs...>;

  template<class... xs>
  using mod = number<(... % xs::value)>;

  template<class... xs>
  using mod0 = call<mp::mod0<>, xs...>;

  template<class... xs>
  using mod1 = call<mp::mod1<>, xs...>;

  template<class... xs>
  using xor_ = number<(... ^ xs::value)>;

  template<class... xs>
  using xor0 = call<mp::xor0<>, xs...>;

  template<class... xs>
  using bit_and = number<(... & xs::value)>;

  template<class... xs>
  using bit_and0 = call<mp::bit_and0<>, xs...>;

  template<class... xs>
  using bit_or = number<(... | xs::value)>;

  template<class... xs>
  using bit_or0 = call<mp::bit_or0<>, xs...>;


  template<class x, class C = mp::identity>
  using neg = call<mp::neg<C>, x>;

  template<class x, class C = mp::identity>
  using unary_plus = call<mp::unary_plus<C>, x>;

  template<class x, class C = mp::identity>
  using not_ = call<mp::not_<C>, x>;

  template<class x, class C = mp::identity>
  using bit_not = call<mp::bit_not<C>, x>;

  template<class x, class C = mp::identity>
  using inc = call<mp::inc<C>, x>;

  template<class x, class C = mp::identity>
  using dec = call<mp::dec<C>, x>;

  template<class x, class y, class C = mp::identity>
  using equal = call<mp::equal<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using not_equal = call<mp::not_equal<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using less = call<mp::less<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using less_equal = call<mp::less_equal<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using greater = call<mp::greater<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using greater_equal = call<mp::greater_equal<C>, x, y>;
}

JLN_DIAGNOSTIC_POP
