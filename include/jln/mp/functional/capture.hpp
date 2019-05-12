#pragma once

#include "../number/number.hpp"

namespace jln::mp
{
  template<class... xs>
  struct capture
  {
    template<class continuation>
    using f = typename continuation::template f<xs...>;
  };
}

namespace jln::vmp
{
  template<int_... ns>
  struct capture_c
  {
    template<class continuation>
    using f = typename continuation::template f<ns...>;
  };

  template<class... xs>
  struct capture_v
  {
    template<class continuation>
    static constexpr int_ f = continuation::template f<xs...>;
  };

  template<int_... ns>
  struct capture_v_c
  {
    template<class continuation>
    static constexpr int_ f = continuation::template f<ns...>;
  };
}
