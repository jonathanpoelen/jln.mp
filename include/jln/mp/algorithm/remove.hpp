#pragma once

#include "../list/join.hpp"
#include "../list/list_wrap_if.hpp"
#include "../utility/same_as.hpp"
#include "transform.hpp"

namespace jln::mp
{
  template<class Pred, class C = listify>
  using remove_if = transform<list_wrap_if_not<Pred>, join<C>>;

  template<class T, class C = listify>
  using remove = remove_if<same_as<T>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using remove_if = unpack<L, mp::remove_if<Pred, C>>;

    template<class L, class T, class C = mp::listify>
    using remove = unpack<L, mp::remove<T, C>>;
  }
}
