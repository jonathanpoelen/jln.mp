#pragma once

#include "capture.hpp"

namespace jln::mp
{
  template<class continuation>
  struct packed
  {
    template<class... xs>
    using f = typename capture<xs...>::template f<continuation>;
  };
}

namespace jln::vmp
{
  template<class continuation>
  struct packed_n
  {
    template<class... ns>
    using f = typename capture_c<ns::value...>::template f<continuation>;
  };

  template<class continuation>
  struct packed_c
  {
    template<int_... ns>
    using f = typename capture_c<ns...>::template f<continuation>;
  };

  template<class continuation>
  struct packed_v
  {
    template<class... xs>
    static constexpr int_ f = capture_v<xs...>::template f<continuation>;
  };

  template<class continuation>
  struct packed_v_n
  {
    template<class... ns>
    static constexpr int_ f = capture_v_c<ns::value...>::template f<continuation>;
  };

  template<class continuation>
  struct packed_v_c
  {
    template<int_... ns>
    static constexpr int_ f = capture_v_c<ns...>::template f<continuation>;
  };
}
