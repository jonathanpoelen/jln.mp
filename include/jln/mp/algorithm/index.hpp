#pragma once

#include "find.hpp"
#include "../list/size.hpp"
#include "../utility/same_as.hpp"

namespace jln::mp
{
  template<class F, class C = identity>
  struct index_for
  {
    template<class... xs>
    using f = typename detail::dcall<(sizeof...(xs) < 1000000)>
      ::template f<C, number<unsigned{int(sizeof...(xs)) - call<F, xs...>::value}>>;
  };

  template<class F>
  struct index_for<F, identity>
  {
    template<class... xs>
    using f = number<unsigned{int(sizeof...(xs)) - call<F, xs...>::value}>;
  };

  template<class Pred, class C = identity, class NC = always<na>>
  using index_if = index_for<find_if<Pred, size<>, NC>, C>;

  template<class T, class C = listify, class NC = always<na>>
  using index_of = index_if<same_as<T>, C, NC>;

  namespace emp
  {
    template<class L, class F, class C = mp::identity>
    using index_for = eager<L, mp::index_for<F, C>>;

    template<class L, class Pred, class C = mp::identity, class NC = mp::always<na>>
    using index_if = eager<L, mp::index_if<Pred, C, NC>>;

    template<class L, class T, class C = mp::identity, class NC = mp::always<na>>
    using index_of = eager<L, mp::index_of<T, C, NC>>;
  }
}
