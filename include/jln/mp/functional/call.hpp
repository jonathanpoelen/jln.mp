#pragma once

#include "../number/number.hpp"

namespace jln::mp
{
  template<class continuation, class... xs>
  using call = typename continuation::template f<xs...>;
}
