#pragma once

#include "../list/list.hpp"
#include "../utility/unpack.hpp"

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, bool>
    struct _powerset;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Computes the powerset of a \sequence.
  /// \semantics
  ///   \code
  ///   call<powerset<>, a, b, c> == list<
  ///     list<>,
  ///     list<a>, list<b>, list<a, b>, list<c>,
  ///     list<a, c>, list<b, c>,
  ///     list<a, b, c>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  template<class C = listify>
  struct powerset
  {
    template<class... xs>
    using f = typename detail::_powerset<C, bool(sizeof...(xs))>
      ::type::template f<list<list<>>, xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using powerset = unpack<L, mp::powerset<C>>;
  }
}


#include "fold_right.hpp"
#include "cartesian.hpp"
#include "../list/front.hpp"
#include "../list/join.hpp"
#include "../functional/call.hpp"
#include "../utility/always.hpp"

/// \cond
namespace jln::mp::detail
{
  template<class, class>
  struct _power;

  template<class... xs, class y>
  struct _power<list<xs...>, y>
  {
    using type = list<list<xs...>, list<y, xs...>>;
  };

  template<class, class>
  struct _powerset_impl;

  template<class... seqs, class y>
  struct _powerset_impl<y, list<seqs...>>
  {
    using type = join<>::f<typename _power<seqs, y>::type...>;
  };

  template<class C, bool>
  struct _powerset
  {
    using type = fold_right<cfl<_powerset_impl>, unpack<C>>;
  };

  template<>
  struct _powerset<listify, true>
  {
    using type = fold_right<cfl<_powerset_impl>>;
  };

  template<class C>
  struct _powerset<C, false>
  {
    using type = _cartesian<C, 0>; // for C::f<>
  };

  template<>
  struct _powerset<listify, false>
  {
    using type = always<list<>>;
  };
}
/// \endcond
