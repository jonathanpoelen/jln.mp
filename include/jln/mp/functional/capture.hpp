#pragma once

namespace jln::mp
{
  template<class... xs>
  struct capture
  {
    template<class C>
    using f = typename C::template f<xs...>;
  };

  template<class... xs>
  struct capture_v
  {
    template<class C>
    using f = typename C::template f<xs::value...>;
  };

  template<auto... ns>
  struct capture_c
  {
    template<class C>
    using f = typename C::template f<ns...>;
  };
}
