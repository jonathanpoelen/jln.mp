#pragma once

#include "../list/list.hpp"
#include "../list/join.hpp"
#include "../functional/call.hpp"

namespace jln::mp
{
  template<class C = listify>
  struct slice
  {
    template<class... xs>
    using f = mp::call<mp::join<C>, xs...>;
  };
}
