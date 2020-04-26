#pragma once

#include "rotate.hpp"


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct _adjacent_difference;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Computes the differences between adjacent_difference pair of elements.
  /// \semantics
  ///   \code
  ///   adjacent_difference_difference<C>::f<a, b, c> = C::f<a, sub::f<a, b>, sub::f<b, c>>
  ///   \endcode
  /// \treturn \sequence
  template<class C = listify>
  struct adjacent_difference
  {
    template<class... xs>
    using f = typename detail::_adjacent_difference<
      rotate_c<-1>::template f<xs...>
    >::template f<C, xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using adjacent_difference = unpack<L, mp::adjacent_difference<C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class y, class... ys>
  struct _adjacent_difference<list<y, ys...>>
  {
    template<class C, class x, class... xs>
    using f = typename C::template f<x, number<xs::value - ys::value>...>;
  };

  template<>
  struct _adjacent_difference<list<>>
  {
    template<class C, class...>
    using f = typename C::template f<>;
  };
}
/// \endcond
