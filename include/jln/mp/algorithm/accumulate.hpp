#pragma once

#include "fold_left.hpp"
#include "../list/join.hpp"
#include "../list/push_front.hpp"
#include "../functional/call.hpp"


namespace jln::mp
{
  template<class F, class C = identity>
  struct accumulate
  {
    template<class state, class... seqs>
    using f = call<join<push_front<state, fold_left<F, C>>>, seqs...>;
  };

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using accumulate = eager<L,
      mp::push_front<state, mp::accumulate<F, C>>>;
  }
}
