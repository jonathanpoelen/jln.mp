#pragma once

#include "../functional/identity.hpp"
#include "number.hpp"

namespace jln::mp
{
  template<class C = identity>
  struct as_number
  {
    template<class x>
    using f = mp::call<C, number<x::value>>;
  };

  namespace emp
  {
    template<class x>
    using as_number = number<x::value>;
  }
}
