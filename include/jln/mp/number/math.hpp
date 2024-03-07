// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/operators.hpp>
#include <jln/mp/list/at.hpp>
#include <jln/mp/functional/flip.hpp>
#include <jln/mp/functional/tee.hpp>
#include <jln/mp/algorithm/fold.hpp>
#include <jln/mp/algorithm/replace.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_ b, int_ e, int_ r = 1>
    constexpr int_ pow_impl_v = pow_impl_v<(b * b), (e / 2), (e % 2 ? b * r : r)>;

    template<int_ b, int_ r>
    constexpr int_ pow_impl_v<b, 0, r> = 1;

    template<int_ b, int_ r>
    constexpr int_ pow_impl_v<b, 1, r> = b * r;

    template<int_ b, int_ r>
    constexpr int_ pow_impl_v<b, -1, r> = 1 / (b * r);

    template<int_ r>
    constexpr int_ pow_impl_v<0, -1, r> = int_{static_cast<int>(r-r)-1}; // inf -> error
  }
  /// \endcond

  /// \ingroup number

  template<class Cmp = less<>, class C = identity>
  using min = fold<if_<flip<Cmp>, at1<>, at0<>>, C>;

  template<class Cmp = less<>, class C = identity>
  using min0 = if_<size<>, min<Cmp, C>, always<number<0>, C>>;


  template<class Cmp = less<>, class C = identity>
  using max = fold<if_<Cmp, at1<>, at0<>>, C>;

  template<class Cmp = less<>, class C = identity>
  using max0 = if_<size<>, max<Cmp, C>, always<number<0>, C>>;


  template<class Min, class Max, class Cmp = less<>, class C = identity>
  using clamp = if_<push_back<Min, Cmp>, always<Min>,
    detail::substitute_if<push_front<Max, Cmp>, Max>>;

  template<int_ min, int_ max, class Cmp = less<>, class C = identity>
  using clamp_c = clamp<number<min>, number<max>, Cmp, C>;


  template<class Cmp = less<>, class C = identity>
  using abs = tee<identity, neg<>, if_<Cmp, at1<C>, at0<C>>>;

  template<class C = identity>
  struct pow
  {
    template<class base, class exponent>
    using f = typename JLN_MP_TRACE_F(C)
      ::template f<number<detail::pow_impl_v<base::value, exponent::value>>>;
  };

  /// \cond
  template<>
  struct pow<identity>
  {
    template<class base, class exponent>
    using f = number<detail::pow_impl_v<base::value, exponent::value>>;
  };
  /// \endcond

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using min = unpack<L, mp::min<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using min0 = unpack<L, mp::min0<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using max = unpack<L, mp::max<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using max0 = unpack<L, mp::max0<Cmp, C>>;

    template<class I, class Min, class Max, class Cmp = mp::less<>, class C = mp::identity>
    using clamp = typename mp::clamp<Min, Max, Cmp, C>::template f<I>;

    template<int_ I, int_ min, int_ max, class Cmp = mp::less<>, class C = mp::identity>
    using clamp_c = typename mp::clamp_c<min, max, Cmp, C>::template f<number<I>>;

    template<class I, class Cmp = mp::less<>, class C = mp::identity>
    using abs = typename mp::abs<Cmp, C>::template f<I>;

    template<int_ I, class Cmp = mp::less<>, class C = mp::identity>
    using abs_c = typename mp::abs<Cmp, C>::template f<number<I>>;

    template<class Base, class Exponent, class C = mp::identity>
    using pow = typename mp::pow<C>::template f<Base, Exponent>;

    template<int_ Base, int_ Exponent, class C = mp::identity>
    using pow_c = typename mp::pow<C>::template f<number<Base>, number<Exponent>>;


    template<class... xs>
    constexpr int_ min_v = mp::min<>::f<xs...>::value;

    template<class... xs>
    constexpr int_ min0_v = mp::min0<>::f<xs...>::value;

    template<int_... xs>
    constexpr int_ min_c_v = mp::min<>::f<number<xs>...>::value;

    template<int_... xs>
    constexpr int_ min0_c_v = mp::min0<>::f<number<xs>...>::value;

    template<class... xs>
    constexpr int_ max_v = mp::max<>::f<xs...>::value;

    template<class... xs>
    constexpr int_ max0_v = mp::max0<>::f<xs...>::value;

    template<int_... xs>
    constexpr int_ max_c_v = mp::max<>::f<number<xs>...>::value;

    template<int_... xs>
    constexpr int_ max0_c_v = mp::max0<>::f<number<xs>...>::value;


    template<class I, class Min, class Max, class Cmp = mp::less<>, class C = mp::identity>
    constexpr int_ clamp_v = mp::clamp<Min, Max, Cmp, C>::template f<I>::value;

    template<int_ I, int_ min, int_ max, class Cmp = mp::less<>, class C = mp::identity>
    constexpr int_ clamp_c_v = mp::clamp_c<min, max, Cmp, C>::template f<number<I>>::value;

    template<class I, class Cmp = mp::less<>, class C = mp::identity>
    constexpr int_ abs_v = mp::abs<Cmp, C>::template f<I>::value;

    template<int_ I, class Cmp = mp::less<>, class C = mp::identity>
    constexpr int_ abs_c_v = mp::abs<Cmp, C>::template f<number<I>>::value;

    template<class Base, class Exponent>
    constexpr int_ pow_v = detail::pow_impl_v<Base::value, Exponent::value>;

    template<int_ base, int_ exponent>
    constexpr int_ pow_c_v = detail::pow_impl_v<base, exponent>;
  }
}
