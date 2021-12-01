#pragma once

#include <jln/mp/value/val.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/detail/call_trace.hpp>

namespace jln::mp
{
  /// \ingroup functional

  template<class... xs>
  struct capture
  {
    template<class C, class... ys>
    using f = JLN_MP_DCALL_TRACE_XS(ys, C, xs..., ys...);
  };

  template<class... xs>
  struct capture_v
  {
    template<class C, class... ys>
    using f = typename JLN_MP_TRACE_F(C)::template f<xs::value..., ys::value...>;
  };

  template<JLN_MP_TPL_AUTO_OR_INT... xs>
  using capture_c = capture<val<xs>...>;

  template<JLN_MP_TPL_AUTO_OR_INT... xs>
  struct capture_v_c
  {
    template<class C, class... ys>
    using f = typename JLN_MP_TRACE_F(C)::template f<xs..., ys::value...>;
  };

  template<class... xs>
  struct reverse_capture
  {
    template<class C, class... ys>
    using f = JLN_MP_DCALL_TRACE_XS(ys, C, ys..., xs...);
  };

  template<class... xs>
  struct reverse_capture_v
  {
    template<class C, class... ys>
    using f = typename JLN_MP_TRACE_F(C)::template f<ys::value..., xs::value...>;
  };

  template<JLN_MP_TPL_AUTO_OR_INT... xs>
  using reverse_capture_c = reverse_capture<val<xs>...>;

  template<JLN_MP_TPL_AUTO_OR_INT... xs>
  struct reverse_capture_v_c
  {
    template<class C, class... ys>
    using f = typename JLN_MP_TRACE_F(C)::template f<ys::value..., xs...>;
  };

}
