#pragma once

#include "../functional/fork.hpp"
#include "../number/operators.hpp"
#include "remove_if.hpp"

namespace jln::mp
{
  template<class Pred, class C = listify>
  using copy_if = transform<if_<Pred, identity, always<list<>>>, C>;
}
