#pragma once

#include "../functional/when.hpp"

namespace jln::mp
{
  template<class C = listify>
  struct pop_front
  {
    template<class x, class... xs>
    using f = mp::call<C, xs...>;
  };
}
