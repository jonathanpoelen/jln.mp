#pragma once

#include "../list/list.hpp"
#include "../list/push_front.hpp"
#include "../utility/unpack.hpp"

namespace jln::mp
{
  template<class L, class C = listify>
  using append = push_front<L, unpack<C>>;
}
