#pragma once

#include "same.hpp"
#include "rotate.hpp"


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct _adjacent_remove;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Removes each element in a \sequence which respect a predicate with privious element.
  /// \treturn \sequence
  template<class BinaryPred, class C = listify>
  struct adjacent_remove_if
  {
    template<class... xs>
    using f = typename detail::_adjacent_remove<
      rotate_c<-1>::template f<xs...>
    >::template f<C, BinaryPred, xs...>;
  };

  /// Removes each element in a \sequence which is the same type as the privious element.
  /// \treturn \sequence
  template<class C = listify>
  using adjacent_remove = adjacent_remove_if<same<>, C>;

  namespace emp
  {
    template<class L, class BinaryPred, class C = mp::listify>
    using adjacent_remove_if = unpack<L, mp::adjacent_remove_if<BinaryPred, C>>;

    template<class L, class C = mp::listify>
    using adjacent_remove = unpack<L, mp::adjacent_remove<C>>;
  }
}


#include "../list/join.hpp"
#include "../list/wrap_in_list.hpp"

/// \cond
namespace jln::mp::detail
{
  template<class y, class... ys>
  struct _adjacent_remove<list<y, ys...>>
  {
    template<class C, class BinaryPred, class x, class... xs>
    using f = typename join<C>::template f<
      list<x>,
      typename wrap_in_list_c<!BinaryPred::template f<xs, ys>::value>::template f<xs>...>;
  };

  template<class>
  struct _adjacent_remove
  {
    template<class C, class...>
    using f = typename C::template f<>;
  };
}
/// \endcond
