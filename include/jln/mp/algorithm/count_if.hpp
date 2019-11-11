#pragma once

#include "copy_if.hpp"
#include "../list/size.hpp"

namespace jln::mp
{
  template<class Pred, class C = listify>
  using count_if = copy_if<Pred, size<C>>;
}
