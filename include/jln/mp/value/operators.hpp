#pragma once

#include "../functional/identity.hpp"
#include "../functional/if.hpp"
#include "../list/push_back.hpp"
#include "../list/size.hpp"
#include "../utility/always.hpp"
#include "../utility/unpack.hpp"
#include "val.hpp"

#include "../../cxx/diagnostic.hpp"

JLN_DIAGNOSTIC_PUSH
JLN_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wlogical-op")

namespace jln::mp
{
  /// \ingroup value

  template<class C = identity>
  struct or_v
  {
    template<class... xs>
    using f = typename C::template f<val<(false || ... || xs::value)>>;
  };

  template<class C = identity>
  struct and_v
  {
    template<class... xs>
    using f = typename C::template f<val<(true && ... && xs::value)>>;
  };

  template<class C = identity>
  struct add_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... + xs::value)>>;
  };

  template<class C = identity>
  using add0_v = if_<size<>, add_v<C>, always<val<0>, C>>;

  template<class C = identity>
  struct sub_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... - xs::value)>>;
  };

  template<class C = identity>
  using sub0_v = if_<size<>, sub_v<C>, always<val<0>, C>>;

  template<class C = identity>
  struct lshift_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... << xs::value)>>;
  };

  template<class C = identity>
  using lshift0_v = if_<size<>, lshift_v<C>, always<val<0>, C>>;

  template<class C = identity>
  struct rshift_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... >> xs::value)>>;
  };

  template<class C = identity>
  using rshift0_v = if_<size<>, rshift_v<C>, always<val<0>, C>>;

  template<class C = identity>
  struct mul_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... * xs::value)>>;
  };

  template<class C = identity>
  using mul0_v = if_<size<>, mul_v<C>, always<val<0>, C>>;

  template<class C = identity>
  using mul1_v = if_<size<>, mul_v<C>, always<val<1>, C>>;

  template<class C = identity>
  struct div_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... / xs::value)>>;
  };

  template<class C = identity>
  using div0_v = if_<size<>, div_v<C>, always<val<0>, C>>;

  template<class C = identity>
  using div1_v = if_<size<>, div_v<C>, always<val<1>, C>>;

  template<class C = identity>
  struct mod_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... %  xs::value)>>;
  };

  template<class C = identity>
  using mod0_v = if_<size<>, mod_v<C>, always<val<0>, C>>;

  template<class C = identity>
  using mod1_v = if_<size<>, mod_v<C>, always<val<1>, C>>;

  template<class C = identity>
  struct xor_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... ^ xs::value)>>;
  };

  template<class C = identity>
  using xor0_v = if_<size<>, xor_v<C>, always<val<0>, C>>;

  template<class C = identity>
  struct bit_and_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... & xs::value)>>;
  };

  template<class C = identity>
  using bit_and0_v = if_<size<>, bit_and_v<C>, always<val<0>, C>>;

  template<class C = identity>
  struct bit_or_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... | xs::value)>>;
  };

  template<class C = identity>
  using bit_or0_v = if_<size<>, bit_or_v<C>, always<val<0>, C>>;

  template<class C = identity>
  struct neg_v
  {
    template<class x>
    using f = typename C::template f<val<(-x::value)>>;
  };

  template<class C = identity>
  struct unary_plus_v
  {
    template<class x>
    using f = typename C::template f<val<(+x::value)>>;
  };

  template<class C = identity>
  struct not_v
  {
    template<class x>
    using f = typename C::template f<val<(!x::value)>>;
  };

  template<class C = identity>
  struct bit_not_v
  {
    template<class x>
    using f = typename C::template f<val<(~x::value)>>;
  };

  template<class C = identity>
  struct inc_v
  {
    template<class x>
    using f = typename C::template f<val<(x::value+1)>>;
  };

  template<class C = identity>
  struct dec_v
  {
    template<class x>
    using f = typename C::template f<val<(x::value-1)>>;
  };

  template<class C = identity>
  struct equal_v
  {
    template<class x, class y>
    using f = typename C::template f<val<(x::value == y::value)>>;
  };

  template<class C = identity>
  struct not_equal_v
  {
    template<class x, class y>
    using f = typename C::template f<val<(x::value != y::value)>>;
  };

  template<class C = identity>
  struct less_v
  {
    template<class x, class y>
    using f = typename C::template f<val<(x::value < y::value)>>;
  };

  template<class C = identity>
  struct less_equal_v
  {
    template<class x, class y>
    using f = typename C::template f<val<(x::value <= y::value)>>;
  };

  template<class C = identity>
  struct greater_v
  {
    template<class x, class y>
    using f = typename C::template f<val<(x::value > y::value)>>;
  };

  template<class C = identity>
  struct greater_equal_v
  {
    template<class x, class y>
    using f = typename C::template f<val<(x::value >= y::value)>>;
  };


  template<class N, class C = identity>
  using equal_than_v = push_back<N, equal_v<C>>;

  template<class N, class C = identity>
  using not_equal_than_v = push_back<N, not_equal_v<C>>;

  template<class N, class C = identity>
  using less_than_v = push_back<N, less_v<C>>;

  template<class N, class C = identity>
  using less_equal_than_v = push_back<N, less_equal_v<C>>;

  template<class N, class C = identity>
  using greater_than_v = push_back<N, greater_v<C>>;

  template<class N, class C = identity>
  using greater_equal_than_v = push_back<N, greater_equal_v<C>>;


  template<auto x, class C = identity>
  using equal_than_c_v = equal_than_v<val<x>, C>;

  template<auto x, class C = identity>
  using not_equal_than_c_v = not_equal_than_v<val<x>, C>;

  template<auto x, class C = identity>
  using less_than_c_v = less_than_v<val<x>, C>;

  template<auto x, class C = identity>
  using less_equal_than_c_v = less_equal_than_v<val<x>, C>;

  template<auto x, class C = identity>
  using greater_than_c_v = greater_than_v<val<x>, C>;

  template<auto x, class C = identity>
  using greater_equal_than_c_v = greater_equal_than_v<val<x>, C>;
}

namespace jln::mp::emp
{
  template<class L, class C = mp::identity>
  using or_seq_v = unpack<L, mp::or_v<C>>;

  template<class L, class C = mp::identity>
  using and_seq_v = unpack<L, mp::and_v<C>>;

  template<class L, class C = mp::identity>
  using add_seq_v = unpack<L, mp::add_v<C>>;

  template<class L, class C = mp::identity>
  using add0_seq_v = unpack<L, mp::add0_v<C>>;

  template<class L, class C = mp::identity>
  using sub_seq_v = unpack<L, mp::sub_v<C>>;

  template<class L, class C = mp::identity>
  using sub0_seq_v = unpack<L, mp::sub0_v<C>>;

  template<class L, class C = mp::identity>
  using lshift_seq_v = unpack<L, mp::lshift_v<C>>;

  template<class L, class C = mp::identity>
  using lshift0_seq_v = unpack<L, mp::lshift0_v<C>>;

  template<class L, class C = mp::identity>
  using rshift_seq_v = unpack<L, mp::rshift_v<C>>;

  template<class L, class C = mp::identity>
  using rshift0_seq_v = unpack<L, mp::rshift0_v<C>>;

  template<class L, class C = mp::identity>
  using mul_seq_v = unpack<L, mp::mul_v<C>>;

  template<class L, class C = mp::identity>
  using mul0_seq_v = unpack<L, mp::mul0_v<C>>;

  template<class L, class C = mp::identity>
  using mul1_seq_v = unpack<L, mp::mul1_v<C>>;

  template<class L, class C = mp::identity>
  using div_seq_v = unpack<L, mp::div_v<C>>;

  template<class L, class C = mp::identity>
  using div0_seq_v = unpack<L, mp::div0_v<C>>;

  template<class L, class C = mp::identity>
  using div1_seq_v = unpack<L, mp::div1_v<C>>;

  template<class L, class C = mp::identity>
  using mod_seq_v = unpack<L, mp::mod_v<C>>;

  template<class L, class C = mp::identity>
  using mod0_seq_v = unpack<L, mp::mod0_v<C>>;

  template<class L, class C = mp::identity>
  using mod1_seq_v = unpack<L, mp::mod1_v<C>>;

  template<class L, class C = mp::identity>
  using xor_seq_v = unpack<L, mp::xor_v<C>>;

  template<class L, class C = mp::identity>
  using xor0_seq_v = unpack<L, mp::xor0_v<C>>;

  template<class L, class C = mp::identity>
  using bit_and_seq_v = unpack<L, mp::bit_and_v<C>>;

  template<class L, class C = mp::identity>
  using bit_and0_seq_v = unpack<L, mp::bit_and0_v<C>>;

  template<class L, class C = mp::identity>
  using bit_or_seq_v = unpack<L, mp::bit_or_v<C>>;

  template<class L, class C = mp::identity>
  using bit_or0_seq_v = unpack<L, mp::bit_or0_v<C>>;


  template<auto... xs>
  using or_c_v = val<(false || ... || xs)>;

  template<auto... xs>
  using and_c_v = val<(true && ... && xs)>;

  template<auto... xs>
  using add_c_v = val<(... + xs)>;

  template<auto... xs>
  using add0_c_v = add_c_v<xs..., 0>;

  template<auto... xs>
  using sub_c_v = val<(... - xs)>;

  template<auto... xs>
  using sub0_c_v = sub_c_v<xs..., 0>;

  template<auto... xs>
  using lshift_c_v = val<(... << xs)>;

  template<auto... xs>
  using lshift0_c_v = lshift_c_v<xs..., 0>;

  template<auto... xs>
  using rshift_c_v = val<(... >> xs)>;

  template<auto... xs>
  using rshift0_c_v = rshift_c_v<xs..., 0>;

  template<auto... xs>
  using mul_c_v = val<(... * xs)>;

  template<auto... xs>
  using mul0_c_v = mul_c_v<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<auto... xs>
  using mul1_c_v = mul_c_v<xs..., 1>;

  template<auto... xs>
  using div_c_v = val<(... / xs)>;

  template<auto... xs>
  using div0_c_v = div_c_v<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<auto... xs>
  using div1_c_v = div_c_v<xs..., 1>;

  template<auto... xs>
  using mod_c_v = val<(... % xs)>;
}

namespace jln::mp::detail
{
  template<bool, template<auto...> class f, int_ d>
  struct _emp_op_v;

  template<template<auto...> class F, int_ d>
  struct _emp_op_v<true, F, d>
  {
    template<auto... xs>
    using f = F<xs...>;
  };

  template<template<auto...> class F, int_ d>
  struct _emp_op_v<false, F, d>
  {
    template<auto...>
    using f = val<d>;
  };
}

namespace jln::mp::emp
{
  template<auto... xs>
  using mod0_c_v = typename detail::_emp_op_v<sizeof...(xs) != 0, mod_c_v, 0>
    ::template f<xs...>;

  template<auto... xs>
  using mod1_c_v = typename detail::_emp_op_v<sizeof...(xs) != 0, mod_c_v, 1>
    ::template f<xs...>;

  template<auto... xs>
  using xor_c_v = val<(... ^ xs)>;

  template<auto... xs>
  using xor0_c_v = xor_c_v<xs..., 0, 0>;

  template<auto... xs>
  using bit_and_c_v = val<(... & xs)>;

  template<auto... xs>
  using bit_and0_c_v = typename detail::_emp_op_v<sizeof...(xs) != 0, bit_and_c_v, 0>
    ::template f<xs...>;

  template<auto... xs>
  using bit_or_c_v = val<(... | xs)>;

  template<auto... xs>
  using bit_or0_c_v = typename detail::_emp_op_v<sizeof...(xs) != 0, bit_or_c_v, 0>
    ::template f<xs...>;


  template<class... xs>
  using or_v = val<(false || ... || xs::value)>;

  template<class... xs>
  using and_v = val<(true && ... && xs::value)>;

  template<class... xs>
  using add_v = val<(... + xs::value)>;

  template<class... xs>
  using add0_v = call<mp::add0_v<>, xs...>;

  template<class... xs>
  using sub_v = val<(... - xs::value)>;

  template<class... xs>
  using sub0_v = call<mp::sub0_v<>, xs...>;

  template<class... xs>
  using lshift_v = val<(... << xs::value)>;

  template<class... xs>
  using lshift0_v = call<mp::lshift0_v<>, xs...>;

  template<class... xs>
  using rshift_v = val<(... >> xs::value)>;

  template<class... xs>
  using rshift0_v = call<mp::rshift0_v<>, xs...>;

  template<class... xs>
  using mul_v = val<(... * xs::value)>;

  template<class... xs>
  using mul0_v = call<mp::mul0_v<>, xs...>;

  template<class... xs>
  using mul1_v = call<mp::mul1_v<>, xs...>;

  template<class... xs>
  using div_v = val<(... / xs::value)>;

  template<class... xs>
  using div0_v = call<mp::div0_v<>, xs...>;

  template<class... xs>
  using div1_v = call<mp::div1_v<>, xs...>;

  template<class... xs>
  using mod_v = val<(... % xs::value)>;

  template<class... xs>
  using mod0_v = call<mp::mod0_v<>, xs...>;

  template<class... xs>
  using mod1_v = call<mp::mod1_v<>, xs...>;

  template<class... xs>
  using xor_v = val<(... ^ xs::value)>;

  template<class... xs>
  using xor0_v = call<mp::xor0_v<>, xs...>;

  template<class... xs>
  using bit_and_v = val<(... & xs::value)>;

  template<class... xs>
  using bit_and0_v = call<mp::bit_and0_v<>, xs...>;

  template<class... xs>
  using bit_or_v = val<(... | xs::value)>;

  template<class... xs>
  using bit_or0_v = call<mp::bit_or0_v<>, xs...>;


  template<class x, class C = mp::identity>
  using neg_v = call<mp::neg_v<C>, x>;

  template<class x, class C = mp::identity>
  using unary_plus_v = call<mp::unary_plus_v<C>, x>;

  template<class x, class C = mp::identity>
  using not_v = call<mp::not_v<C>, x>;

  template<class x, class C = mp::identity>
  using bit_not_v = call<mp::bit_not_v<C>, x>;

  template<class x, class C = mp::identity>
  using inc_v = call<mp::inc_v<C>, x>;

  template<class x, class C = mp::identity>
  using dec_v = call<mp::dec_v<C>, x>;

  template<class x, class y, class C = mp::identity>
  using equal_v = call<mp::equal_v<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using not_equal_v = call<mp::not_equal_v<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using less_v = call<mp::less_v<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using less_equal_v = call<mp::less_equal_v<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using greater_v = call<mp::greater_v<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using greater_equal_v = call<mp::greater_equal_v<C>, x, y>;
}

JLN_DIAGNOSTIC_POP
