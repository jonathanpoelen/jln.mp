#pragma once

#include "../functional/identity.hpp"
#include "../utility/eager.hpp"

namespace jln::mp
{
  template<class C = identity>
  struct front
  {
    template<class x, class... xs>
    using f = typename C::template f<x>;
  };

  template<>
  struct front<identity>
  {
    template<class x, class...>
    using f = x;
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using front = eager<L, front<C>>;
  }
}
