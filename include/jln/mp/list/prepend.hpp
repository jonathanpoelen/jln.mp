#pragma once

#include "../list/list.hpp"
#include "../list/push_front.hpp"
#include "../utility/unpack.hpp"

namespace jln::mp
{
  template<class L, class C = listify>
  using prepend = push_front<L, unpack<C>>;

  namespace emp
  {
    template<class L, class... xs>
    using prepend = typename unpack<listify>::template f<L, xs...>;
  }
}
