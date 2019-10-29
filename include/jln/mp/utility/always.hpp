#pragma once

#include "../functional/identity.hpp"

namespace jln::mp
{
  template<class x, class C = identity>
  struct always
  {
    template<class... xs>
    using f = typename C::template f<x>;
  };
}
