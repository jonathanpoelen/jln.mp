#pragma once

#include "../functional/when.hpp"
#include "../list/pop_front.hpp"
#include "../list/push_back.hpp"
#include "../number/number.hpp"

#include "../../cxx/diagnostic.hpp"

JLN_DIAGNOSTIC_PUSH
JLN_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wlogical-op")

namespace jln::mp
{
  // TODO C++20 value<(... @ xs::value)> ? other namespace ?
  // TODO @_righr = number<(value @ ...)>
  // TODO @_v

  // TODO add0 = number<(value @ ... @ 0)>

  template<class C = identity>
  struct or_
  {
    template<class... xs>
    using f = typename C::template f<number<(... || xs::value)>>;
  };

  template<class C = identity>
  struct and_
  {
    template<class... xs>
    using f = typename C::template f<number<(... && xs::value)>>;
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
  using mul0 = if_<size<>, always<number<0>, C>, mul<C>>;

  template<class C = identity>
  using mul1 = mp::push_back<number<1>, mul<C>>;

  template<class C = identity>
  struct div
  {
    template<class... xs>
    using f = typename C::template f<number<(... / xs::value)>>;
  };

  template<class C = identity>
  using div0 = if_<size<>, always<number<0>, C>, div<C>>;

  template<class C = identity>
  using div1 = mp::push_back<number<1>, add<C>>;

  template<class C = identity>
  struct mod
  {
    template<class... xs>
    using f = typename C::template f<number<(... %  xs::value)>>;
  };

  template<class C = identity>
  using mod0 = if_<size<>, always<number<0>, C>, mod<C>>;

  template<class C = identity>
  using mod1 = if_<size<>, always<number<1>, C>, mod<C>>;

  template<class C = identity>
  struct xor_
  {
    template<class... xs>
    using f = typename C::template f<number<(... ^ xs::value)>>;
  };

  template<class C = identity>
  using xor0 = if_<size<>, always<number<0>, C>, xor_<C>>;

  template<class C = identity>
  struct bit_and
  {
    template<class... xs>
    using f = typename C::template f<number<(... & xs::value)>>;
  };

  template<class C = identity>
  using bit_and0 = if_<size<>, always<number<0>, C>, bit_and<C>>;

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
}

namespace jln::mp
{
  template<class F, class C = listify>
  struct transform
  {
    template<class... xs>
    using f = call<C, call<F, xs>...>;
  };

  template<class F, class C = identity>
  using all_of = mp::transform<F, mp::and_<C>>;

  template<class C, class FC = unsatisfactory_concept>
  using monadic_invoke = if_<
   transform<
     same_as<unsatisfactory_concept_error>, or_<>>,
   FC, C
  >;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using transform = eager<L, mp::transform<C>>;
  }

  namespace smp
  {
    template<class F, class C = listify>
    using transform = when<
      mp::always<mp::true_>,
      mp::transform<
        mp::try_invoke<when_continuation<F>>,
        mp::monadic_invoke<when_continuation<C>>
      >
    >;
  }
}

namespace jln::mp
{
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

  namespace smp
  {
    template<class C = identity>
    using or_ = when<
      mp::all_of<mp::has_value<>>,
      mp::or_<when_continuation<C>>>;

    template<class C = identity>
    using and_ = when<
      mp::all_of<mp::has_value<>>,
      mp::and_<when_continuation<C>>>;

    template<class C = identity>
    using add = when<
      mp::if_<mp::size<>, mp::all_of<mp::has_value<>>>,
      mp::add<when_continuation<C>>>;

    template<class C = identity>
    using add0 = when<
      mp::all_of<mp::has_value<>>,
      mp::add0<when_continuation<C>>>;

    template<class C = identity>
    using sub = when<
      mp::if_<mp::size<>, mp::all_of<mp::has_value<>>>,
      mp::sub<when_continuation<C>>>;

    template<class C = identity>
    using sub0 = when<
      mp::all_of<mp::has_value<>>,
      mp::sub0<when_continuation<C>>>;

    template<class C = identity>
    using lshift = when<
      mp::if_<mp::size<>, mp::all_of<mp::has_value<>>>,
      mp::lshift<when_continuation<C>>>;

    template<class C = identity>
    using lshift0 = when<
      mp::all_of<mp::has_value<>>,
      mp::lshift0<when_continuation<C>>>;

    template<class C = identity>
    using rshift = when<
      mp::if_<mp::size<>, mp::all_of<mp::has_value<>>>,
      mp::rshift<when_continuation<C>>>;

    template<class C = identity>
    using rshift0 = when<
      mp::all_of<mp::has_value<>>,
      mp::rshift0<when_continuation<C>>>;

    template<class C = identity>
    using mul = when<
      mp::if_<mp::size<>, mp::all_of<mp::has_value<>>>,
      mp::mul<when_continuation<C>>>;

    template<class C = identity>
    using mul0 = when<
      mp::all_of<mp::has_value<>>,
      mp::mul0<when_continuation<C>>>;

    template<class C = identity>
    using mul1 = when<
      mp::all_of<mp::has_value<>>,
      mp::mul1<when_continuation<C>>>;

    template<class C = identity>
    using div = when<
      mp::if_<
        mp::size<>,
        mp::if_<
          mp::all_of<mp::has_value<>>,
          mp::pop_front<mp::and_<>>>>,
      mp::div<when_continuation<C>>>;

    template<class C = identity>
    using div0 = when<
      mp::all_of<mp::has_value<>>,
      mp::if_<
        mp::size<>,
        mp::if_<
          mp::pop_front<mp::and_<>>,
          mp::div<when_continuation<C>>,
          mp::unsatisfactory_concept>,
        mp::always<number<0>, when_continuation<C>>>>;

    template<class C = identity>
    using div1 = when<
      mp::all_of<mp::has_value<>>,
      mp::if_<
        mp::size<>,
        mp::if_<
          mp::pop_front<mp::and_<>>,
          mp::div<when_continuation<C>>,
          mp::unsatisfactory_concept>,
        mp::always<number<1>, when_continuation<C>>>>;

    template<class C = identity>
    using mod = when<
      mp::if_<
        mp::size<>,
        mp::if_<
          mp::all_of<mp::has_value<>>,
          mp::pop_front<mp::and_<>>>>,
      mp::mod<when_continuation<C>>>;

    template<class C = identity>
    using mod0 = when<
      mp::all_of<mp::has_value<>>,
      mp::if_<
        mp::size<>,
        mp::if_<
          mp::pop_front<mp::and_<>>,
          mp::mod<when_continuation<C>>,
          mp::unsatisfactory_concept>,
        mp::always<number<0>, when_continuation<C>>>>;

    template<class C = identity>
    using mod1 = when<
      mp::all_of<mp::has_value<>>,
      mp::if_<
        mp::size<>,
        mp::if_<
          mp::pop_front<mp::and_<>>,
          mp::mod<when_continuation<C>>,
          mp::unsatisfactory_concept>,
        mp::always<number<1>, when_continuation<C>>>>;

    template<class C = identity>
    using xor_ = when<
      mp::if_<mp::size<>, mp::all_of<mp::has_value<>>>,
      mp::xor_<when_continuation<C>>>;

    template<class C = identity>
    using xor0 = when<
      mp::all_of<mp::has_value<>>,
      mp::xor0<when_continuation<C>>>;

    template<class C = identity>
    using bit_and = when<
      mp::if_<mp::size<>, mp::all_of<mp::has_value<>>>,
      mp::bit_and<when_continuation<C>>>;

    template<class C = identity>
    using bit_and0 = when<
      mp::all_of<mp::has_value<>>,
      mp::bit_and0<when_continuation<C>>>;

    template<class C = identity>
    using bit_or = when<
      mp::if_<mp::size<>, mp::all_of<mp::has_value<>>>,
      mp::bit_or<when_continuation<C>>>;

    template<class C = identity>
    using bit_or0 = when<
      mp::all_of<mp::has_value<>>,
      mp::bit_or0<when_continuation<C>>>;

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
      mp::if_<mp::size_of_2<>, mp::all_of<mp::has_value<>>>,
      mp::equal<when_continuation<C>>>;

    template<class C = identity>
    using not_equal = when<
      mp::if_<mp::size_of_2<>, mp::all_of<mp::has_value<>>>,
      mp::not_equal<when_continuation<C>>>;

    template<class C = identity>
    using less = when<
      mp::if_<mp::size_of_2<>, mp::all_of<mp::has_value<>>>,
      mp::less<when_continuation<C>>>;

    template<class C = identity>
    using less_equal = when<
      mp::if_<mp::size_of_2<>, mp::all_of<mp::has_value<>>>,
      mp::less_equal<when_continuation<C>>>;

    template<class C = identity>
    using greater = when<
      mp::if_<mp::size_of_2<>, mp::all_of<mp::has_value<>>>,
      mp::greater<when_continuation<C>>>;

    template<class C = identity>
    using greater_equal = when<
      mp::if_<mp::size_of_2<>, mp::all_of<mp::has_value<>>>,
      mp::greater_equal<when_continuation<C>>>;
  }
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, or_<C>>
  {
    using type = smp::or_<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, and_<C>>
  {
    using type = smp::and_<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, add<C>>
  {
    using type = smp::add<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, sub<C>>
  {
    using type = smp::sub<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, lshift<C>>
  {
    using type = smp::lshift<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, rshift<C>>
  {
    using type = smp::rshift<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, mul<C>>
  {
    using type = smp::mul<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, div<C>>
  {
    using type = smp::div<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, mod<C>>
  {
    using type = smp::mod<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, xor_<C>>
  {
    using type = smp::xor_<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, bit_and<C>>
  {
    using type = smp::bit_and<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, bit_or<C>>
  {
    using type = smp::bit_or<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, neg<C>>
  {
    using type = smp::neg<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unary_plus<C>>
  {
    using type = smp::unary_plus<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, not_<C>>
  {
    using type = smp::not_<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, bit_not<C>>
  {
    using type = smp::bit_not<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, inc<C>>
  {
    using type = smp::inc<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, dec<C>>
  {
    using type = smp::dec<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, equal<C>>
  {
    using type = smp::equal<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, not_equal<C>>
  {
    using type = smp::not_equal<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, less<C>>
  {
    using type = smp::less<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, less_equal<C>>
  {
    using type = smp::less_equal<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, greater<C>>
  {
    using type = smp::greater<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, greater_equal<C>>
  {
    using type = smp::greater_equal<sfinae<C>>;
  };
}

JLN_DIAGNOSTIC_POP
