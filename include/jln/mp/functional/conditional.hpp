#pragma once

namespace jln::mp
{
  template<bool>
  struct conditional_c
  {
    template<class x, class y>
    using f = x;
  };

  template<>
  struct conditional_c<false>
  {
    template<class x, class y>
    using f = y;
  };

  template<class v>
  using conditional = conditional_c<bool(v::value)>;

  namespace eager
  {
    template<class v, class x, class y>
    using conditional = typename conditional_c<bool(v::value)>::template f<x, y>;

    template<bool cond, class x, class y>
    using conditional_c = typename conditional_c<cond>::template f<x, y>;
  }
}
