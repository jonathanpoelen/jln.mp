#pragma once

#include "../list/list.hpp"
#include "../list/push_front.hpp"
#include "../utility/unpack_append.hpp"

namespace jln::mp
{
  template<class L, class C = listify>
  using append = push_front<L, unpack_append<C>>;

  namespace emp
  {
    template<class L, class... xs>
    using append = typename unpack_append<listify>::template f<L, xs...>;
  }
}
