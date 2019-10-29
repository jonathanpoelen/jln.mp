#pragma once

#include "unpack.hpp"

namespace jln::mp
{
  template<class L, class C>
  using eager = typename mp::unpack<C>::template f<L>;
}
