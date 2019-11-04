#pragma once

namespace jln::mp
{
  template<class C>
  struct values
  {
    template<class... ns>
    using f = typename C::template f<ns::value...>;
  };

  template<class C>
  struct typed_values
  {
    template<class x, class... ns>
    using f = typename C::template f<x, ns::value...>;
  };
}
