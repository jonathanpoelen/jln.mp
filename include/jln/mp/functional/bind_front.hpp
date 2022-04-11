#pragma once

#include <jln/mp/value/val.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Invoking \c F with its first parameters bound to bound to args.
  /// \semantics
  ///   \code
  ///   bind_front<F, a, b>::f<c, d> == F<a, b, c, d>
  ///   \endcode
  /// \treturn \sequence
  /// \see bind_back, capture_front, capture_back
  template<class F, class... BoundArgs>
  struct bind_front
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, F, BoundArgs..., xs...);
  };

  template<class F, int_... BoundArgs>
  using bind_front_c = bind_front<F, number<BoundArgs>...>;

#if JLN_MP_ENABLE_TPL_AUTO
  template<class F, auto... BoundArgs>
  using bind_front_v = bind_front<F, val<BoundArgs>...>;
#endif

  namespace emp
  {
    template<class L, class F, class... BoundArgs>
    using bind_front = unpack<L, mp::bind_front<F, BoundArgs...>>;

    template<class L, class F, int_... BoundArgs>
    using bind_front_c = unpack<L, mp::bind_front_c<F, BoundArgs...>>;

#if JLN_MP_ENABLE_TPL_AUTO
    template<class L, class F, auto... BoundArgs>
    using bind_front_v = unpack<L, mp::bind_front_v<F, BoundArgs...>>;
#endif
  }
} // namespace jln::mp
