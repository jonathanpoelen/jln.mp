#pragma once

namespace jln::mp
{
  /// \ingroup functional

  template<class... xs>
  struct capture
  {
    template<class C, class... ys>
    using f = typename C::template f<xs..., ys...>;
  };

  template<class... xs>
  struct capture_v
  {
    template<class C, class... ys>
    using f = typename C::template f<xs::value..., ys::value...>;
  };

  template<auto... xs>
  struct capture_c
  {
    template<class C, auto... ys>
    using f = typename C::template f<xs..., ys...>;
  };

  template<class... xs>
  struct reverse_capture
  {
    template<class C, class... ys>
    using f = typename C::template f<ys..., xs...>;
  };

  template<class... xs>
  struct reverse_capture_v
  {
    template<class C, class... ys>
    using f = typename C::template f<ys::value..., xs::value...>;
  };

  template<auto... xs>
  struct reverse_capture_c
  {
    template<class C, auto... ys>
    using f = typename C::template f<ys..., xs...>;
  };
}
