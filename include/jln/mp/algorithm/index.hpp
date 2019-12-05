#pragma once

#include "find.hpp"
#include "../list/size.hpp"
#include "../list/offset.hpp"
#include "../utility/same_as.hpp"

namespace jln::mp
{
  template<class Pred, class C = identity, class NC = always<na>>
  struct index_if
  {
    template<class... xs>
    using f = typename find_if<Pred, offset<number<sizeof...(xs)>, C>, NC>
      ::template f<xs...>;
  };

  template<class T, class C = listify, class NC = always<na>>
  using index_of = index_if<same_as<T>, C, NC>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity, class NC = mp::always<na>>
    using index_if = eager<L, mp::index_if<Pred, C, NC>>;

    template<class L, class T, class C = mp::identity, class NC = mp::always<na>>
    using index_of = eager<L, mp::index_of<T, C, NC>>;
  }
}
