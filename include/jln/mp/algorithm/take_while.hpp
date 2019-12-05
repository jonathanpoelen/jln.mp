#pragma once

#include "index.hpp"
#include "../list/take.hpp"
#include "../functional/bind.hpp"
#include "../functional/fork.hpp"
#include "../functional/fork_front.hpp"
#include "../utility/always.hpp"

namespace jln::mp
{
  template<class Pred, class C = listify>
  using take_while = fork_front<fork<
    index_if<Pred, identity, always<number<0>>>,
    always<C>,
    cfe<take>
  >>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using take_while = eager<L, mp::take_while<Pred, C>>;
  }
}
