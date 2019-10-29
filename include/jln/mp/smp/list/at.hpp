#pragma once

#include "../algorithm/drop_front.hpp"
#include "front.hpp"

namespace jln::mp
{
  template<class C = identity>
  using at0 = drop_front<number<1>, C>;

  template<class C = identity>
  using at1 = drop_front<number<2>, front<C>>;

  namespace emp
  {
    template<class L, class i, class C = mp::identity>
    using at = eager<L, drop_front<number<i::value+1>, front<C>>>;

    template<class L, int_ i, class C = mp::identity>
    using at_c = eager<L, drop_front<number<i+1>, front<C>>>;
  }

  // TODO smp
}
