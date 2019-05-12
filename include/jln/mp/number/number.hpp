#pragma once

#include <cstdint>

namespace jln::mp
{
  using int_ = std::intmax_t;

  template<int_ v>
  struct number { static const int_ value = v; };

  using true_ = number<1>;
  using false_ = number<0>;
}
