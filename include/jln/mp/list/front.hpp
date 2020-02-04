#pragma once

#include "../functional/identity.hpp"
#include "../utility/eager.hpp"

namespace jln::mp
{
  // TODO at<0>
  template<class C = identity>
  struct front
  {
    template<class x, class... xs>
    using f = typename C::template f<x>;
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using front = eager<L, front<C>>;
  }
}
