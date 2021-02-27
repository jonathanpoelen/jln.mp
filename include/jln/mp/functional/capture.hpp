#pragma once

#include <jln/mp/value/val.hpp>
#include <jln/mp/number/number.hpp>

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

#if __cplusplus >= 201703L
  template<auto... xs>
  using capture_c = capture<val<xs>...>;

  template<auto... xs>
  struct capture_v_c
#else
  template<int_... xs>
  using capture_c = capture<number<xs>...>;

  template<int_... xs>
  struct capture_v_c
#endif
  {
    template<class C, class... ys>
    using f = typename C::template f<xs..., ys::value...>;
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

#if __cplusplus >= 201703L
  template<auto... xs>
  using reverse_capture_c = reverse_capture<val<xs>...>;

  template<auto... xs>
  struct reverse_capture_v_c
#else
  template<int_... xs>
  using reverse_capture_c = reverse_capture<number<xs>...>;

  template<int_... xs>
  struct reverse_capture_v_c
#endif
  {
    template<class C, class... ys>
    using f = typename C::template f<ys::value..., xs...>;
  };

}
