#pragma once

#include <jln/mp/number/operators.hpp>
#include <jln/mp/list/at.hpp>
#include <jln/mp/functional/flip.hpp>
#include <jln/mp/functional/tee.hpp>
#include <jln/mp/algorithm/fold_left.hpp>
#include <jln/mp/algorithm/replace.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_ b, int_ e, int_ r = 1>
    struct _ipow;

    template<class base, class exponent>
    using _pow = typename _ipow<base::value, exponent::value, 1>::type;
  }
  /// \endcond

  /// \ingroup number

  template<class Cmp = less<>, class C = identity>
  using min = fold_left<if_<flip<Cmp>, at1<>, at0<>>, C>;

  template<class Cmp = less<>, class C = identity>
  using min0 = if_<size<>, min<Cmp, C>, always<number<0>, C>>;


  template<class Cmp = less<>, class C = identity>
  using max = fold_left<if_<Cmp, at1<>, at0<>>, C>;

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
  using pow = fold_left<lift<detail::_pow>, C>;

  template<class C = identity>
  using pow0 = if_<size<>, pow<C>, always<number<0>, C>>;

  template<class C = identity>
  using pow1 = if_<size<>, pow<C>, always<number<1>, C>>;


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

    template<class L, class C = mp::identity>
    using pow = unpack<L, mp::pow<C>>;

    template<class L, class C = mp::identity>
    using pow0 = unpack<L, mp::pow0<C>>;

    template<class L, class C = mp::identity>
    using pow1 = unpack<L, mp::pow1<C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<int_ b, int_ e, int_ r>
  struct _ipow
  : _ipow<(b * b), (e / 2), (e % 2 ? b * r : r)>
  {};

  template<int_ b, int_ r>
  struct _ipow<b, 0, r>
  {
    using type = number<1>;
  };

  template<int_ b, int_ r>
  struct _ipow<b, 1, r>
  {
    using type = number<b * r>;
  };

  template<int_ b, int_ r>
  struct _ipow<b, -1, r>
  {
    using type = number<1 / (b * r)>;
  };

  template<int_ r>
  struct _ipow<0, -1, r>
  {};
}
/// \endcond
