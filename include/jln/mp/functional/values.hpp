#pragma once

namespace jln::mp
{
  template<class continuation>
  struct values
  {
    template<class... ns>
    using f = typename continuation::template f<ns::value...>;
  };

  template<class continuation>
  struct typed_values
  {
    template<class x, class... ns>
    using f = typename continuation::template f<x, ns::value...>;
  };
}
