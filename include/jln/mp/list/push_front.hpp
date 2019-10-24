#pragma once

#include "../functional/when.hpp"

namespace jln::mp
{
  template<class T, class C = listify>
  struct push_front
  {
    template<class... xs>
    using f = mp::call<C, T, xs...>;
  };
}
