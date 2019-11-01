#pragma once

#include "drop.hpp"

namespace jln::mp
{
  template<class C = listify>
  using pop_front = drop<number<1>, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using pop_front = drop<L, mp::number<1>, C>;
  }
}
