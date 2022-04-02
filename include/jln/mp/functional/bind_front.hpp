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

  template<class F, class... BoundArgs>
  struct bind_front_v
  {
    template<class... xs>
    using f = typename conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
      ::template f<JLN_MP_TRACE_F(F), ::jln::mp::detail::too_many_arguments_error>
      ::template f<BoundArgs::value..., xs::value...>;
  };

#if __cplusplus >= 201703L
  template<class F, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  using bind_front_c = bind_front<F, val<BoundArgs>...>;
#else
  template<class F, int_... BoundArgs>
  using bind_front_c = bind_front<F, typed_val<int_, BoundArgs>...>;
#endif

  template<class F, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  struct bind_front_v_c
  {
    template<class... xs>
    using f = typename F::template f<BoundArgs..., xs::value...>;
  };

  namespace emp
  {
    template<class L, class F, class... BoundArgs>
    using bind_front = unpack<L, mp::bind_front<F, BoundArgs...>>;

    template<class L, class F, class... BoundArgs>
    using bind_front_v = unpack<L, mp::bind_front_v<F, BoundArgs...>>;

    template<class L, class F, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
    using bind_front_v_c = unpack<L, mp::bind_front_v_c<F, BoundArgs...>>;
  }
} // namespace jln::mp
