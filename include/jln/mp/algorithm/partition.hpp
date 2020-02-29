#pragma once

#include "remove.hpp"
#include "copy.hpp"
#include "../functional/fork.hpp"

namespace jln::mp
{
  template<class Pred, class C = listify>
  using partition = fork<remove_if<Pred>, copy_if<Pred>, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using partition = unpack<L, mp::partition<C>>;
  }
}
