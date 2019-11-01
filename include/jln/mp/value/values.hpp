#pragma once

namespace jln::mp
{
  template<class C>
  struct values
  {
    template<class... xs>
    using f = typename C::template f<xs::value...>;
  };

  template<class C>
  struct typed_values
  {
    template<class x, class... xs>
    using f = typename C::template f<x, xs::value...>;
  };
}
