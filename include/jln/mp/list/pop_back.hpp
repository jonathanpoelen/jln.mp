#pragma once

#include "pop_front.hpp"
#include "../algorithm/rotate.hpp"

namespace jln::mp
{
  template<class C = listify>
  using pop_back = rotate<number<-1>, pop_front<C>>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using pop_back = eager<L, mp::pop_back<C>>;
  }
}
