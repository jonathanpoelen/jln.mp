#pragma once

#include "front.hpp"
#include "../algorithm/rotate.hpp"

namespace jln::mp
{
  template<class C = identity>
  using back = rotate<number<-1>, front<C>>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using back = eager<L, mp::back<C>>;
  }
}
