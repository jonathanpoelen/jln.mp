#pragma once

#include <jln/mp/value/val.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/utility/conditional.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Invoking \c F with its last parameters bound to bound to args.
  /// \semantics
  ///   \code
  ///   capture_back<c, d>::f<F, a, b> == F<a, b, c, d>
  ///   \endcode
  /// \treturn \sequence
  /// \see capture_front, bind_back, bind_front
  template<class... BoundArgs>
  struct capture_back
  {
    template<class F, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, F, xs..., BoundArgs...);
  };

#if __cplusplus >= 201703L
  template<JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  using capture_back_c = capture_back<val<BoundArgs>...>;
#else
  template<int_... BoundArgs>
  using capture_back_c = capture_back<typed_val<int_, BoundArgs>...>;
#endif

  template<JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  struct capture_back_v_c
  {
    template<class F, class... xs>
    using f = typename F::template f<xs::value..., BoundArgs...>;
  };

  template<class... BoundArgs>
  using capture_back_v = capture_back_v_c<BoundArgs::value...>;

  namespace emp
  {
    template<class L, class... BoundArgs>
    using capture_back = unpack<L, mp::capture_back<BoundArgs...>>;

    template<class L, class... BoundArgs>
    using capture_back_v = unpack<L, mp::capture_back_v<BoundArgs...>>;

    template<class L, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
    using capture_back_v_c = unpack<L, mp::capture_back_v_c<BoundArgs...>>;
  }
}
