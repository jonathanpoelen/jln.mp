#pragma once

#include "../list/list.hpp"
#include "../list/join.hpp"
#include "rotate.hpp"
#include "remove_if.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<class L1, class L2>
    struct _remove_adjacent;
  }

  template<class Cmp, class C = listify>
  struct remove_adjacent_if
  {
    template<class... xs>
    using f = typename detail::_remove_adjacent<
      list<xs...>,
      rotate_c<-1>::template f<xs...>
    >::template f<C, Cmp>;
  };

  namespace emp
  {
    template<class L, class Cmp, class C = mp::listify>
    using remove_adjacent_if = eager<L, mp::remove_adjacent_if<Cmp, C>>;
  }
}

namespace jln::mp::detail
{
  // TODO _remove_adjacent<list<y, ys...>, x, xs...>
  template<class x, class... xs, class y, class... ys>
  struct _remove_adjacent<list<x, xs...>, list<y, ys...>>
  {
    // TODO struct<Cmp> for memoization of Cmp<xs, ys> ?
    // TODO template<class...> class Cmp is better ?
    template<class C, class Cmp>
    using f = typename join<C>::template f<
      list<x>,
      typename _wrap_if<!Cmp::template f<xs, ys>::value>::template f<xs>...>;
  };

  template<class, class>
  struct _remove_adjacent
  {
    template<class C, class>
    using f = typename C::template f<>;
  };
}
