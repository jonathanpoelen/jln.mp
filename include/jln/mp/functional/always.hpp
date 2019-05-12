#pragma once

#include "identity.hpp"

namespace jln::mp
{
  template<class x, class continuation = identity>
  struct always
  {
    template<class... xs>
    using f = typename continuation::template f<x>;
  };
} // namespace jln::mp
