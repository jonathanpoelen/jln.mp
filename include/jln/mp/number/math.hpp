#pragma once

#include "operators.hpp"
#include "../list/at.hpp"
#include "../functional/flip.hpp"
#include "../algorithm/fold_left.hpp"

namespace jln::mp
{
  namespace detail
  {
    struct _pow;
  }

  template<class Pred = less<>, class C = identity>
  using min = fold_left<if_<flip<Pred>, at1<>, at0<>>, C>;

  template<class Pred = less<>, class C = identity>
  using min0 = if_<size<>, min<Pred, C>, always<number<0>, C>>;


  template<class Pred = less<>, class C = identity>
  using max = fold_left<if_<Pred, at1<>, at0<>>, C>;

  template<class Pred = less<>, class C = identity>
  using max0 = if_<size<>, max<Pred, C>, always<number<0>, C>>;


  template<class Pred = less<>, class C = identity>
  using abs = fork<identity, neg<>, max<Pred, C>>;


  template<class C = identity>
  using pow = fold_left<detail::_pow, C>;

  template<class C = identity>
  using pow0 = if_<size<>, pow<C>, always<number<0>, C>>;

  template<class C = identity>
  using pow1 = if_<size<>, pow<C>, always<number<1>, C>>;


  namespace emp
  {
    template<class L, class Pred = mp::less<>, class C = mp::identity>
    using min = eager<L, mp::min<Pred, C>>;

    template<class L, class Pred = mp::less<>, class C = mp::identity>
    using min0 = eager<L, mp::min0<Pred, C>>;

    template<class L, class Pred = mp::less<>, class C = mp::identity>
    using max = eager<L, mp::max<Pred, C>>;

    template<class L, class Pred = mp::less<>, class C = mp::identity>
    using max0 = eager<L, mp::max0<Pred, C>>;

    template<class L, class Pred = mp::less<>, class C = mp::identity>
    using abs = eager<L, mp::abs<Pred, C>>;

    template<class L, class C = mp::identity>
    using pow = eager<L, mp::pow<C>>;

    template<class L, class C = mp::identity>
    using pow0 = eager<L, mp::pow0<C>>;

    template<class L, class C = mp::identity>
    using pow1 = eager<L, mp::pow1<C>>;
  }
}

namespace jln::mp::detail
{
  template<int_ b, int_ e, int_ r = 1>
  struct _ipow
  : _ipow<(b * b), (e / 2), (e % 2 ? b * r : r)>
  {};

  struct _pow
  {
    template<class base, class exponent>
    using f = typename _ipow<base::value, exponent::value, 1>::type;
  };

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
