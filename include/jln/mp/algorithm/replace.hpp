#pragma once

#include "../list/list.hpp"
#include "../list/join.hpp"
#include "../functional/if.hpp"
#include "transform.hpp"

namespace jln::mp
{
  template<class Pred, class T, class C = listify>
  using replace_if = transform<if_<Pred, always<T>, identity>, C>;

  template<class T, class U, class C = listify>
  using replace = replace_if<same_as<T>, U, C>;

  namespace emp
  {
    template<class L, class T, class U, class C = mp::listify>
    using replace = unpack<L, mp::replace<T, U, C>>;

    template<class L, class Pred, class T, class C = mp::listify>
    using replace_if = unpack<L, mp::replace_if<Pred, T, C>>;
  }
}
