#pragma once

#include "same.hpp"
#include "rotate.hpp"


namespace jln::mp
{
  namespace detail
  {
    template<class>
    struct _remove_adjacent;
  }

  template<class Cmp, class C = listify>
  struct remove_adjacent_if
  {
    template<class... xs>
    using f = typename detail::_remove_adjacent<
      rotate_c<-1>::template f<xs...>
    >::template f<C, Cmp, xs...>;
  };

  template<class C = listify>
  using remove_adjacent = remove_adjacent_if<same<>, C>;

  namespace emp
  {
    template<class L, class Cmp, class C = mp::listify>
    using remove_adjacent_if = eager<L, mp::remove_adjacent_if<Cmp, C>>;

    template<class L, class C = mp::listify>
    using remove_adjacent = eager<L, mp::remove_adjacent<C>>;
  }
}


#include "../list/join.hpp"
#include "../list/list_wrap_if.hpp"

namespace jln::mp::detail
{
  template<class y, class... ys>
  struct _remove_adjacent<list<y, ys...>>
  {
    template<class C, class Cmp, class x, class... xs>
    using f = typename join<C>::template f<
      list<x>,
      typename list_wrap_if_c<!Cmp::template f<xs, ys>::value>::template f<xs>...>;
  };

  template<class>
  struct _remove_adjacent
  {
    template<class C, class...>
    using f = typename C::template f<>;
  };
}
