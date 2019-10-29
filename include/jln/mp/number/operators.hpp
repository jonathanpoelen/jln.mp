#pragma once

#include "../functional/identity.hpp"
#include "../functional/if.hpp"
#include "../list/push_back.hpp"
#include "../list/size.hpp"
#include "../number/number.hpp"
#include "../utility/always.hpp"
#include "../utility/eager.hpp"

#include "../../cxx/diagnostic.hpp"

// TODO under condition ?
JLN_DIAGNOSTIC_PUSH
JLN_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wlogical-op")

// value/operators.hpp

namespace jln::mp
{
  // TODO C++20 value<(... @ xs::value)> ? other namespace ?
  // TODO @_right = number<(value @ ...)>
  // TODO @_v and emp::@_c

  // TODO add0 = number<(value @ ... @ 0)>

  // TODO equal_than<N> and co

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
  using add0 = mp::push_back<number<0>, add<C>>;

  template<class C = identity>
  struct sub
  {
    template<class... xs>
    using f = typename C::template f<number<(... - xs::value)>>;
  };

  template<class C = identity>
  using sub0 = mp::push_back<number<0>, sub<C>>;

  template<class C = identity>
  struct lshift
  {
    template<class... xs>
    using f = typename C::template f<number<(... << xs::value)>>;
  };

  template<class C = identity>
  using lshift0 = mp::push_back<number<0>, lshift<C>>;

  template<class C = identity>
  struct rshift
  {
    template<class... xs>
    using f = typename C::template f<number<(... >> xs::value)>>;
  };

  template<class C = identity>
  using rshift0 = mp::push_back<number<0>, rshift<C>>;

  template<class C = identity>
  struct mul
  {
    template<class... xs>
    using f = typename C::template f<number<(... * xs::value)>>;
  };

  template<class C = identity>
  using mul0 = if_<size<>, mul<C>, always<number<0>, C>>;

  template<class C = identity>
  using mul1 = mp::push_back<number<1>, mul<C>>;

  template<class C = identity>
  struct div
  {
    template<class... xs>
    using f = typename C::template f<number<(... / xs::value)>>;
  };

  template<class C = identity>
  using div0 = if_<size<>, div<C>, always<number<0>, C>>;

  template<class C = identity>
  using div1 = mp::push_back<number<1>, add<C>>;

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
  using bit_or0 = mp::push_back<number<0>, bit_or<C>>;

  template<class C = identity>
  struct neg
  {
    template<class x>
    using f = number<(-x::value)>;
  };

  template<class C = identity>
  struct unary_plus
  {
    template<class x>
    using f = number<(+x::value)>;
  };

  template<class C = identity>
  struct not_
  {
    template<class x>
    using f = number<(!x::value)>;
  };

  template<class C = identity>
  struct bit_not
  {
    template<class x>
    using f = number<(~x::value)>;
  };

  template<class C = identity>
  struct inc
  {
    template<class x>
    using f = number<(x::value+1)>;
  };

  template<class C = identity>
  struct dec
  {
    template<class x>
    using f = number<(x::value-1)>;
  };

  template<class C = identity>
  struct equal
  {
    template<class x, class y>
    using f = number<(x::value == y::value)>;
  };

  template<class C = identity>
  struct not_equal
  {
    template<class x, class y>
    using f = number<(x::value != y::value)>;
  };

  template<class C = identity>
  struct less
  {
    template<class x, class y>
    using f = number<(x::value < y::value)>;
  };

  template<class C = identity>
  struct less_equal
  {
    template<class x, class y>
    using f = number<(x::value <= y::value)>;
  };

  template<class C = identity>
  struct greater
  {
    template<class x, class y>
    using f = number<(x::value > y::value)>;
  };

  template<class C = identity>
  struct greater_equal
  {
    template<class x, class y>
    using f = number<(x::value >= y::value)>;
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
}

namespace jln::mp::emp
{
  template<class L, class C = mp::identity>
  using or_ = eager<L, mp::or_<C>>;

  template<class L, class C = mp::identity>
  using and_ = eager<L, mp::and_<C>>;

  template<class L, class C = mp::identity>
  using add = eager<L, mp::add<C>>;

  template<class L, class C = mp::identity>
  using sub = eager<L, mp::sub<C>>;

  template<class L, class C = mp::identity>
  using sub0 = eager<L, mp::sub0<C>>;

  template<class L, class C = mp::identity>
  using lshift = eager<L, mp::lshift<C>>;

  template<class L, class C = mp::identity>
  using lshift0 = eager<L, mp::lshift0<C>>;

  template<class L, class C = mp::identity>
  using rshift = eager<L, mp::rshift<C>>;

  template<class L, class C = mp::identity>
  using rshift0 = eager<L, mp::rshift0<C>>;

  template<class L, class C = mp::identity>
  using mul = eager<L, mp::mul<C>>;

  template<class L, class C = mp::identity>
  using mul0 = eager<L, mp::mul0<C>>;

  template<class L, class C = mp::identity>
  using mul1 = eager<L, mp::mul1<C>>;

  template<class L, class C = mp::identity>
  using div = eager<L, mp::div<C>>;

  template<class L, class C = mp::identity>
  using div0 = eager<L, mp::div0<C>>;

  template<class L, class C = mp::identity>
  using div1 = eager<L, mp::div1<C>>;

  template<class L, class C = mp::identity>
  using mod = eager<L, mp::mod<C>>;

  template<class L, class C = mp::identity>
  using mod0 = eager<L, mp::mod0<C>>;

  template<class L, class C = mp::identity>
  using mod1 = eager<L, mp::mod1<C>>;

  template<class L, class C = mp::identity>
  using xor_ = eager<L, mp::xor_<C>>;

  template<class L, class C = mp::identity>
  using xor0 = eager<L, mp::xor0<C>>;

  template<class L, class C = mp::identity>
  using bit_and = eager<L, mp::bit_and<C>>;

  template<class L, class C = mp::identity>
  using bit_and0 = eager<L, mp::bit_and0<C>>;

  template<class L, class C = mp::identity>
  using bit_or = eager<L, mp::bit_or<C>>;

  template<class L, class C = mp::identity>
  using bit_or0 = eager<L, mp::bit_or0<C>>;

  template<class L, class C = mp::identity>
  using neg = eager<L, mp::neg<C>>;

  template<class L, class C = mp::identity>
  using unary_plus = eager<L, mp::unary_plus<C>>;

  template<class L, class C = mp::identity>
  using not_ = eager<L, mp::not_<C>>;

  template<class L, class C = mp::identity>
  using bit_not = eager<L, mp::bit_not<C>>;

  template<class L, class C = mp::identity>
  using inc = eager<L, mp::inc<C>>;

  template<class L, class C = mp::identity>
  using dec = eager<L, mp::dec<C>>;

  template<class L, class C = mp::identity>
  using equal = eager<L, mp::equal<C>>;

  template<class L, class C = mp::identity>
  using not_equal = eager<L, mp::not_equal<C>>;

  template<class L, class C = mp::identity>
  using less = eager<L, mp::less<C>>;

  template<class L, class C = mp::identity>
  using less_equal = eager<L, mp::less_equal<C>>;

  template<class L, class C = mp::identity>
  using greater = eager<L, mp::greater<C>>;

  template<class L, class C = mp::identity>
  using greater_equal = eager<L, mp::greater_equal<C>>;
}

JLN_DIAGNOSTIC_POP
