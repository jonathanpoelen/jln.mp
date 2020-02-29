#pragma once

#include "../list/drop.hpp"
#include "../list/take.hpp"
#include "../functional/fork.hpp"

namespace jln::mp
{
  template<class i, class C = listify>
  using split_at = fork<take<i>, drop<i>, C>;

  template<int_ i, class C = listify>
  using split_at_c = split_at<number<i>, C>;

  namespace emp
  {
    template<class L, class i, class C = mp::listify>
    using split_at = unpack<L, mp::split_at<i, C>>;

    template<class L, int_ i, class C = mp::listify>
    using split_at_c = unpack<L, mp::split_at_c<i, C>>;
  }
}
