// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/operators.hpp>
#include <jln/mp/functional/select.hpp>
#include <limits>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_ b, int_ e, int_ r = 1>
    inline constexpr int_ pow_impl_v = pow_impl_v<(b * b), (e / 2), (e % 2 ? b * r : r)>;

    template<int_ b, int_ r>
    inline constexpr int_ pow_impl_v<b, 0, r> = 1;

    template<int_ b, int_ r>
    inline constexpr int_ pow_impl_v<b, 1, r> = b * r;

    template<int_ b, int_ r>
    inline constexpr int_ pow_impl_v<b, -1, r> = 1 / (b * r);

    template<int_ r>
    inline constexpr int_ pow_impl_v<0, -1, r> = int_{static_cast<int>(r-r)-1}; // inf -> error

    template<class T>
    struct abs_impl;
  }
  /// \endcond

  /// \ingroup number

  template<class C = identity>
  using min = reverse_select_flip<less<>, C>;

  template<class C = identity>
  using max = reverse_select<less<>, C>;


  template<class Min, class Max, class Cmp = less<>, class C = identity>
  struct clamp_with
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C,
      typename conditional_c<
        JLN_MP_TRACE_F(Cmp)::template f<x, Min>::value
      >::template f<
        Min,
        typename conditional_c<
          JLN_MP_TRACE_F(Cmp)::template f<Max, x>::value
        >::template f<Max, x>
      >
    );
  };

  template<class Min, class Max, class C = identity>
  using clamp = clamp_with<Min, Max, less<>, C>;

  template<int_ min, int_ max, class Cmp = less<>, class C = identity>
  using clamp_with_c = clamp_with<number<min>, number<max>, Cmp, C>;

  template<int_ min, int_ max, class C = identity>
  using clamp_c = clamp_with<number<min>, number<max>, less<>, C>;


  template<class C = identity>
  struct abs
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::abs_impl<const volatile decltype(x::value)&>::template f<x>
    );
  };


  template<class C = identity>
  struct pow
  {
    template<class base, class exponent>
    using f = typename JLN_MP_TRACE_F(C)
      ::template f<number<detail::pow_impl_v<base::value, exponent::value>>>;
  };

  namespace emp
  {
    template<class x, class y, class C = mp::identity>
    inline constexpr auto min_v = JLN_MP_TRACE_F(C)::template f<
      typename mp::conditional_c<y::value < x::value>::template f<y, x>
    >::value;

    template<class x, class y>
    inline constexpr auto min_v<x, y> = mp::conditional_c<y::value < x::value>
      ::template f<y, x>::value;

    template<int_ x, int_ y, class C = mp::identity>
    inline constexpr auto min_c_v = JLN_MP_TRACE_F(C)
      ::template f<number<y < x ? y : x>>::value;

    template<int_ x, int_ y>
    inline constexpr int_ min_c_v<x, y> = y < x ? y : x;

    template<class x, class y, class C = mp::identity>
    using min = typename mp::select<mp::less<>, C>::template f<x, y>;

    template<int_ x, int_ y, class C = mp::identity>
    using min_c = JLN_MP_CALL_TRACE(C, number<y < x ? y : x>);


    template<class x, class y, class C = mp::identity>
    inline constexpr auto max_v = JLN_MP_TRACE_F(C)::template f<
      typename mp::conditional_c<x::value < y::value>::template f<y, x>
    >::value;

    template<class x, class y>
    inline constexpr auto max_v<x, y> = mp::conditional_c<x::value < y::value>
      ::template f<y, x>::value;

    template<int_ x, int_ y, class C = mp::identity>
    inline constexpr auto max_c_v = JLN_MP_TRACE_F(C)
      ::template f<number<x < y ? y : x>>::value;

    template<int_ x, int_ y>
    inline constexpr int_ max_c_v<x, y> = x < y ? y : x;

    template<class x, class y, class C = mp::identity>
    using max = typename mp::reverse_select<mp::less<>, C>::template f<x, y>;

    template<int_ x, int_ y, class C = mp::identity>
    using max_c = JLN_MP_CALL_TRACE(C, number<x < y ? y : x>);


    template<class I, class Min, class Max, class C = mp::identity>
    inline constexpr auto clamp_v = mp::clamp_with<Min, Max, mp::less<>, C>
      ::template f<I>::value;

    template<int_ i, int_ min, int_ max, class C = mp::identity>
    inline constexpr auto clamp_c_v = JLN_MP_TRACE_F(C)
      ::template f<number<i < min ? min : max < i ? max : i>>::value;

    template<int_ i, int_ min, int_ max>
    inline constexpr int_ clamp_c_v<i, min, max> = i < min ? min : max < i ? max : i;

    template<class I, class Min, class Max, class C = mp::identity>
    using clamp = typename mp::clamp_with<Min, Max, mp::less<>, C>::template f<I>;

    template<int_ i, int_ min, int_ max, class C = mp::identity>
    using clamp_c = JLN_MP_CALL_TRACE(C, number<(i < min ? min : max < i ? max : i)>);


    template<class I, class Min, class Max, class Cmp = mp::less<>, class C = mp::identity>
    inline constexpr auto clamp_with_v = mp::clamp_with<Min, Max, Cmp, C>
      ::template f<I>::value;

    template<int_ i, int_ min, int_ max, class Cmp = mp::less<>, class C = mp::identity>
    inline constexpr auto clamp_with_c_v = JLN_MP_TRACE_F(C)
      ::template f<number<clamp_with_c_v<i, min, max, Cmp>>>::value;

    template<int_ i, int_ min, int_ max, class Cmp>
    inline constexpr int_ clamp_with_c_v<i, min, max, Cmp> =
      JLN_MP_TRACE_F(Cmp)::template f<number<i>, number<min>>::value
        ? min
        : JLN_MP_TRACE_F(Cmp)::template f<number<max>, number<i>>::value
          ? max
          : i;

    template<int_ i, int_ min, int_ max, class C>
    inline constexpr auto clamp_with_c_v<i, min, max, mp::less<>, C> =
      JLN_MP_TRACE_F(C)::template f<number<i < min ? min : max < i ? max : i>>::value;

    template<int_ i, int_ min, int_ max>
    inline constexpr int_ clamp_with_c_v<i, min, max> = i < min ? min : max < i ? max : i;

    template<class I, class Min, class Max, class Cmp = mp::less<>, class C = mp::identity>
    using clamp_with = typename mp::clamp_with<Min, Max, Cmp, C>::template f<I>;

    template<int_ i, int_ min, int_ max, class Cmp = mp::less<>, class C = mp::identity>
    using clamp_with_c = typename mp::clamp_with_c<min, max, Cmp, C>::template f<number<i>>;


    template<class I, class C = mp::identity>
    inline constexpr auto abs_v = mp::abs<C>::template f<I>::value;

    template<int_ i, class C = mp::identity>
    inline constexpr auto abs_c_v = JLN_MP_TRACE_F(C)
      ::template f<number<abs_c_v<i>>>::value;

    template<int_ i>
    inline constexpr int_ abs_c_v<i> = (i < -i ? -i : i)
      + !sizeof(int[std::numeric_limits<int_>::min() != i]); // check abs(-min)


    template<class I, class C = mp::identity>
    using abs = typename mp::abs<C>::template f<I>;

    template<int_ i, class C = mp::identity>
    using abs_c = JLN_MP_CALL_TRACE(C, number<abs_c_v<i>>);


    template<class Base, class Exponent, class C = mp::identity>
    inline constexpr int_ pow_v = JLN_MP_TRACE_F(C)
      ::template f<number<detail::pow_impl_v<Base::value, Exponent::value>>>::value;

    template<class Base, class Exponent>
    inline constexpr int_ pow_v<Base, Exponent> = detail::pow_impl_v<Base::value, Exponent::value>;

    template<int_ base, int_ exponent, class C = mp::identity>
    inline constexpr int_ pow_c_v = JLN_MP_TRACE_F(C)
      ::template f<number<detail::pow_impl_v<base, exponent>>>::value;

    template<int_ base, int_ exponent>
    inline constexpr int_ pow_c_v<base, exponent> = detail::pow_impl_v<base, exponent>;


    template<class Base, class Exponent, class C = mp::identity>
    using pow = typename mp::pow<C>::template f<Base, Exponent>;

    template<int_ base, int_ exponent, class C = mp::identity>
    using pow_c = JLN_MP_CALL_TRACE(C, number<detail::pow_impl_v<base, exponent>>);
  }
}

/// \cond
namespace jln::mp
{
  template<class Min, class Max>
  struct clamp_with<Min, Max, less<>, identity>
  {
    template<class x>
    using f =
      typename conditional_c<x::value < Min::value>
      ::template f<
        Min,
        typename conditional_c<Max::value < x::value>
        ::template f<Max, x>
      >
    ;
  };

  template<class Min, class Max, class Cmp>
  struct clamp_with<Min, Max, Cmp, identity>
  {
    template<class x>
    using f =
      typename conditional_c<
        JLN_MP_TRACE_F(Cmp)::template f<x, Min>::value
      >::template f<
        Min,
        typename conditional_c<
          JLN_MP_TRACE_F(Cmp)::template f<Max, x>::value
        >::template f<Max, x>
      >;
  };

  template<class Min, class Max, class C>
  struct clamp_with<Min, Max, less<>, C>
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C,
      typename conditional_c<x::value < Min::value>::template f<
        Min,
        typename conditional_c<Max::value < x::value>
        ::template f<Max, x>
      >
    );
  };

  template<>
  struct abs<identity>
  {
    template<class x>
    using f = typename detail::abs_impl<const volatile decltype(x::value)&>::template f<x>;
  };

  template<>
  struct pow<identity>
  {
    template<class base, class exponent>
    using f = number<detail::pow_impl_v<base::value, exponent::value>>;
  };
}

namespace jln::mp::detail
{
  struct abs_negate_min_value_error
  {
    template<int> using f = abs_negate_min_value_error;
  };

  struct abs_unspecialized_numeric_limits_error
  {
    template<int> using f = abs_unspecialized_numeric_limits_error;
  };

  template<class T>
  struct abs_signed
  {
    template<class x>
    using f = typename conditional_c<std::numeric_limits<T>::min() == x::value>
      ::template f<
        abs_negate_min_value_error,
        conditional_c<x::value < -x::value>
      >
      ::template f<number<-x::value>, x>;
  };

  template<bool, bool>
  struct abs_select_impl : always<abs_unspecialized_numeric_limits_error>
  {};

  template<>
  struct abs_select_impl<true, true>
  {
    template<class T>
    using f = abs_signed<T>;
  };

  template<>
  struct abs_select_impl<true, false> : always<identity>
  {};

  template<class T>
  struct abs_impl : abs_select_impl<
    std::numeric_limits<T>::is_specialized,
    std::numeric_limits<T>::is_signed
  >::template f<T>
  {};

  template<class T> struct abs_impl<const volatile T> : abs_impl<T> {};
  template<class T> struct abs_impl<const volatile T&> : abs_impl<T> {};
  template<class T> struct abs_impl<const volatile T&&> : abs_impl<T> {};
  template<class T> struct abs_impl<T&> : abs_impl<const volatile T> {};
  template<class T> struct abs_impl<T&&> : abs_impl<const volatile T> {};
}
/// \endcond
