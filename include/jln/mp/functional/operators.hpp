#pragma once

#include "../functional/when.hpp"
#include "../number/number.hpp"


namespace jln::mp
{
  template<class C = identity>
  struct or_
  {
    template<class... xs>
    using f = typename C::template f<number<(xs::value || ...)>>;
  };

  template<class C = identity>
  struct and_
  {
    template<class... xs>
    using f = typename C::template f<number<(xs::value && ...)>>;
  };

  template<class C = identity>
  struct add
  {
    template<class... xs>
    using f = typename C::template f<number<(xs::value + ... + 0)>>;
  };

  template<class C = identity>
  struct sub
  {
    template<class... xs>
    using f = typename C::template f<number<(xs::value - ... - 0)>>;
  };

  template<class C = identity>
  struct lshift
  {
    template<class... xs>
    using f = typename C::template f<number<(xs::value << ... << 0)>>;
  };

  template<class C = identity>
  struct rshift
  {
    template<class... xs>
    using f = typename C::template f<number<(xs::value >> ... >> 0)>>;
  };

  template<class C = identity>
  struct mul
  {
    template<class... xs>
    using f = typename C::template f<number<(xs::value * ... * 1)>>;
  };

  template<class C = identity>
  struct div
  {
    template<class... xs>
    using f = typename C::template f<number<(xs::value / ... / 1)>>;
  };

  template<class C = identity>
  struct mod
  {
    template<class... xs>
    using f = typename C::template f<number<(xs::value % ... % 1)>>;
  };

  template<class C = identity>
  struct xor_
  {
    template<class... xs>
    using f = typename C::template f<number<(xs::value ^ ... ^ 0)>>;
  };

  template<class C = identity>
  struct bit_and
  {
    template<class... xs>
    using f = typename C::template f<number<(xs::value & ... & 0)>>;
  };

  template<class C = identity>
  struct bit_or
  {
    template<class... xs>
    using f = typename C::template f<number<(xs::value | ... | 0)>>;
  };

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

  namespace emp
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
    using lshift = eager<L, mp::lshift<C>>;

    template<class L, class C = mp::identity>
    using rshift = eager<L, mp::rshift<C>>;

    template<class L, class C = mp::identity>
    using mul = eager<L, mp::mul<C>>;

    template<class L, class C = mp::identity>
    using div = eager<L, mp::div<C>>;

    template<class L, class C = mp::identity>
    using mod = eager<L, mp::mod<C>>;

    template<class L, class C = mp::identity>
    using xor_ = eager<L, mp::xor_<C>>;

    template<class L, class C = mp::identity>
    using bit_and = eager<L, mp::bit_and<C>>;

    template<class L, class C = mp::identity>
    using bit_or = eager<L, mp::bit_or<C>>;

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

  namespace smp
  {
    template<class C = identity>
    using or_ = when<mp::has_value<>,
      mp::or_<when_continuation<C>>>;

    template<class C = identity>
    using and_ = when<mp::has_value<>,
      mp::and_<when_continuation<C>>>;

    template<class C = identity>
    using add = when<mp::has_value<>,
      mp::add<when_continuation<C>>>;

    template<class C = identity>
    using sub = when<mp::has_value<>,
      mp::sub<when_continuation<C>>>;

    template<class C = identity>
    using lshift = when<mp::has_value<>,
      mp::lshift<when_continuation<C>>>;

    template<class C = identity>
    using rshift = when<mp::has_value<>,
      mp::rshift<when_continuation<C>>>;

    template<class C = identity>
    using mul = when<mp::has_value<>,
      mp::mul<when_continuation<C>>>;

    template<class C = identity>
    using div = when<
      mp::if_<mp::has_value<>, mp::and_<>>,
      mp::div<when_continuation<C>>>;

    template<class C = identity>
    using mod = when<
      mp::if_<mp::has_value<>, mp::and_<>>,
      mp::mod<when_continuation<C>>>;

    template<class C = identity>
    using xor_ = when<mp::has_value<>,
      mp::xor_<when_continuation<C>>>;

    template<class C = identity>
    using bit_and = when<mp::has_value<>,
      mp::bit_and<when_continuation<C>>>;

    template<class C = identity>
    using bit_or = when<mp::has_value<>,
      mp::bit_or<when_continuation<C>>>;

    template<class C = identity>
    using neg = when<
      mp::if_<mp::size_of_1<>, mp::has_value<>>,
      mp::neg<when_continuation<C>>>;

    template<class C = identity>
    using unary_plus = when<
      mp::if_<mp::size_of_1<>, mp::has_value<>>,
      mp::unary_plus<when_continuation<C>>>;

    template<class C = identity>
    using not_ = when<
      mp::if_<mp::size_of_1<>, mp::has_value<>>,
      mp::not_<when_continuation<C>>>;

    template<class C = identity>
    using bit_not = when<
      mp::if_<mp::size_of_1<>, mp::has_value<>>,
      mp::bit_not<when_continuation<C>>>;

    template<class C = identity>
    using inc = when<
      mp::if_<mp::size_of_1<>, mp::has_value<>>,
      mp::inc<when_continuation<C>>>;

    template<class C = identity>
    using dec = when<
      mp::if_<mp::size_of_1<>, mp::has_value<>>,
      mp::dec<when_continuation<C>>>;

    template<class C = identity>
    using equal = when<
      mp::if_<mp::size_of_2<>, mp::has_value<>>,
      mp::equal<when_continuation<C>>>;

    template<class C = identity>
    using not_equal = when<
      mp::if_<mp::size_of_2<>, mp::has_value<>>,
      mp::not_equal<when_continuation<C>>>;

    template<class C = identity>
    using less = when<
      mp::if_<mp::size_of_2<>, mp::has_value<>>,
      mp::less<when_continuation<C>>>;

    template<class C = identity>
    using less_equal = when<
      mp::if_<mp::size_of_2<>, mp::has_value<>>,
      mp::less_equal<when_continuation<C>>>;

    template<class C = identity>
    using greater = when<
      mp::if_<mp::size_of_2<>, mp::has_value<>>,
      mp::greater<when_continuation<C>>>;

    template<class C = identity>
    using greater_equal = when<
      mp::if_<mp::size_of_2<>, mp::has_value<>>,
      mp::greater_equal<when_continuation<C>>>;
  }
}
