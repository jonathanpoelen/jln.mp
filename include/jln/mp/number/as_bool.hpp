#pragma once

#include "../functional/identity.hpp"
#include "../functional/call.hpp"
#include "number.hpp"

namespace jln::mp
{
  template<class C = identity>
  struct as_bool
  {
    template<class x>
    using f = call<C, number<x::value ? 1 : 0>>;
  };

  namespace emp
  {
    template<class x>
    using as_bool = number<x::value>;
  }
}
