#pragma once

#include "../list/join.hpp"
#include "../list/drop.hpp"
#include "../list/take.hpp"
#include "../utility/always.hpp"
#include "../functional/fork.hpp"

namespace jln::mp
{
  template<class i, class seq, class C = listify>
  using insert = fork<take<i>, always<seq>, drop<i>, join<C>>;

  template<int_ i, class seq, class C = listify>
  using insert_c = insert<number<i>, seq, C>;

  namespace emp
  {
    template<class L, class i, class seq, class C = mp::listify>
    using insert = eager<L, mp::insert<i, seq, C>>;

    template<class L, int_ i, class seq, class C = mp::listify>
    using insert_c = insert<L, number<i>, seq, C>;
  }
}
