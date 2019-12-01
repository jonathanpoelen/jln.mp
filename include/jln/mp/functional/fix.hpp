#pragma once

#include "../functional/call.hpp"

namespace jln::mp
{
  template<class C>
  struct fix
  {
    template<class... xs>
    using f = call<C, fix<C>, xs...>;
  };
}
