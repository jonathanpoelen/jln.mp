#pragma once

#include "../number/number.hpp"
#include "../functional/identity.hpp"
#include "../utility/eager.hpp"

namespace jln::mp
{
  template <class I, class C = identity>
  struct offset
  {
    template <class... xs>
    using f = call<C, number<(I::value - int_{sizeof...(xs)})>>;
  };

  template<int_ i, class C = identity>
  using offset_c = offset<number<i>, C>;

  namespace emp
  {
    template<class L, class I, class C = mp::identity>
    using offset = eager<L, mp::offset<I, C>>;

    template<class L, int_ i, class C = mp::identity>
    using offset_c = eager<L, mp::offset<number<i>, C>>;
  }
}
