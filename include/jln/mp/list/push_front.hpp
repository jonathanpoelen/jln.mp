#pragma once

#include "list.hpp"
#include "../functional/call.hpp"

namespace jln::mp
{
  template<class T, class C = listify>
  struct push_front
  {
    template<class... xs>
    using f = call<C, T, xs...>;
  };

  namespace emp
  {
    template<class L, class T, class C = mp::listify>
    using push_front = eager<L, mp::push_front<T, C>>;
  }
}
