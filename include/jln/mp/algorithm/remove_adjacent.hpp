#pragma once

#include "same.hpp"
#include "rotate.hpp"


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct _remove_adjacent;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Removes each element in a \sequence which respect a predicate with privious element.
  /// \return \sequence
  template<class BinaryPred, class C = listify>
  struct remove_adjacent_if
  {
    template<class... xs>
    using f = typename detail::_remove_adjacent<
      rotate_c<-1>::template f<xs...>
    >::template f<C, BinaryPred, xs...>;
  };

  /// Removes each element in a \sequence which is the same type as the privious element.
  /// \return \sequence
  template<class C = listify>
  using remove_adjacent = remove_adjacent_if<same<>, C>;

  namespace emp
  {
    template<class L, class BinaryPred, class C = mp::listify>
    using remove_adjacent_if = unpack<L, mp::remove_adjacent_if<BinaryPred, C>>;

    template<class L, class C = mp::listify>
    using remove_adjacent = unpack<L, mp::remove_adjacent<C>>;
  }
}


#include "../list/join.hpp"
#include "../list/list_wrap_if.hpp"

/// \cond
namespace jln::mp::detail
{
  template<class y, class... ys>
  struct _remove_adjacent<list<y, ys...>>
  {
    template<class C, class BinaryPred, class x, class... xs>
    using f = typename join<C>::template f<
      list<x>,
      typename list_wrap_if_c<!BinaryPred::template f<xs, ys>::value>::template f<xs>...>;
  };

  template<class>
  struct _remove_adjacent
  {
    template<class C, class...>
    using f = typename C::template f<>;
  };
}
/// \endcond
