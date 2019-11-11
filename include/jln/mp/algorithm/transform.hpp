#pragma once

#include "../list/list.hpp"
#include "../utility/eager.hpp"
#include "../functional/call.hpp"


namespace jln::mp
{
  template<class F, class C = listify>
  struct transform
  {
    template<class... xs>
    using f = dispatch<C, F, xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using transform = eager<L, mp::transform<C>>;
  }
}
