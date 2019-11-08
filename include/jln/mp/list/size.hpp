#pragma once

#include "../number/number.hpp"
#include "../utility/eager.hpp"

namespace jln::mp
{
  template<class C = identity>
  struct size
  {
    template<class... xs>
    using f = typename C::template f<number<sizeof...(xs)>>;
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using size = eager<L, mp::size<C>>;
  }
}
