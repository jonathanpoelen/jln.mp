#pragma once

#include "../list/join.hpp"
#include "../list/drop.hpp"
#include "../list/take.hpp"
#include "../utility/always.hpp"
#include "../functional/fork.hpp"

namespace jln::mp
{
  template<class i, class seq, class C = listify>
  using splice = fork<take<i>, always<seq>, drop<i>, join<C>>;

  template<int_ i, class seq, class C = listify>
  using splice_c = splice<number<i>, seq, C>;

  namespace emp
  {
    template<class L, class i, class seq, class C = mp::listify>
    using splice = eager<L, mp::splice<i, seq, C>>;

    template<class L, int_ i, class seq, class C = mp::listify>
    using splice_c = eager<L, mp::splice_c<i, seq, C>>;
  }
}
