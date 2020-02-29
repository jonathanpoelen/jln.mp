#pragma once

#include "split.hpp"

namespace jln::mp
{
  template<class Pred, class C = listify>
  struct split_after_if
  {
    template <class... xs>
    using f = typename detail::_split<sizeof...(xs) != 0>
      ::template f<detail::split_after, C, Pred, xs...>;
  };

  template<class x, class C = listify>
  using split_after = split_after_if<same_as<x>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using split_after_if = unpack<L, mp::split_after_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using split_after = unpack<L, mp::split_after<x, C>>;
  }
}
