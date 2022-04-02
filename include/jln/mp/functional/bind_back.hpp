#pragma once

#include <jln/mp/value/val.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Invoking \c F with its last parameters bound to bound to args.
  /// \semantics
  ///   \code
  ///   bind_back<F, c, d>::f<a, b> == F<a, b, c, d>
  ///   \endcode
  /// \treturn \sequence
  /// \see bind_front, capture_back, capture_front
  template<class F, class... BoundArgs>
  struct bind_back
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, F, xs..., BoundArgs...);
  };

  template<class F, class... BoundArgs>
  struct bind_back_v
  {
    template<class... xs>
    using f = typename conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
      ::template f<JLN_MP_TRACE_F(F), ::jln::mp::detail::too_many_arguments_error>
      ::template f<xs::value..., BoundArgs::value...>;
  };

#if __cplusplus >= 201703L
  template<class F, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  using bind_back_c = bind_back<F, val<BoundArgs>...>;
#else
  template<class F, int_... BoundArgs>
  using bind_back_c = bind_back<F, typed_val<int_, BoundArgs>...>;
#endif

  template<class F, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  struct bind_back_v_c
  {
    template<class... xs>
    using f = typename F::template f<BoundArgs..., xs::value...>;
  };

  namespace emp
  {
    template<class L, class F, class... BoundArgs>
    using bind_back = unpack<L, mp::bind_back<F, BoundArgs...>>;

    template<class L, class F, class... BoundArgs>
    using bind_back_v = unpack<L, mp::bind_back_v<F, BoundArgs...>>;

    template<class L, class F, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
    using bind_back_v_c = unpack<L, mp::bind_back_v_c<F, BoundArgs...>>;
  }
} // namespace jln::mp
