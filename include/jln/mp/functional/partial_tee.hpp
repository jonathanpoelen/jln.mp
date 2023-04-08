#pragma once

#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/functional/lift.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, class... Fs>
    struct partial_tee_impl;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions passing all parameters to each
  /// then calls \c C with the results and the rest of the parameters.
  /// \semantics
  ///   \code
  ///   partial_tee<F,G,C>::f<a> == /* error */
  ///   partial_tee<F,G,C>::f<a,b,c,d> == C::f<F::f<a,b,c,d>, G::f<a,b,c,d>, c, d>
  ///   \endcode
  /// \treturn \value
  /// \see partial_each, partial, each, tee
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct partial_tee
  {
    template<class... xs>
    using f;
  };
#else
  template<class... Fs>
  struct partial_tee
  : detail::rotate_impl<sizeof...(Fs)-1>
  ::template f<sizeof...(Fs)-1, lift<detail::partial_tee_impl>, Fs...>
  {};
#endif
}

#include <jln/mp/list/join.hpp>
#include <jln/mp/list/drop_front.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class C, class... Fs>
  struct partial_tee_impl
  {
    template<class... xs>
    using f = typename join<C>::template f<
      list<JLN_MP_DCALL_TRACE_XS(xs, Fs, xs...)...>,
      typename drop_front_c<sizeof...(xs) - sizeof...(Fs)>::template f<xs...>
    >;
  };

  template<class C, class F0, class F1, class F2, class F3>
  struct partial_tee_impl<C, F0, F1, F2, F3>
  {
    template<class x0, class x1, class x2, class x3,
             class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0, x1, x2, x3, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F1, x0, x1, x2, x3, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F2, x0, x1, x2, x3, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F3, x0, x1, x2, x3, xs...),
      xs...
    );
  };

  template<class C, class F0, class F1, class F2>
  struct partial_tee_impl<C, F0, F1, F2>
  {
    template<class x0, class x1, class x2, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0, x1, x2, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F1, x0, x1, x2, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F2, x0, x1, x2, xs...),
      xs...
    );
  };

  template<class C, class F0, class F1>
  struct partial_tee_impl<C, F0, F1>
  {
    template<class x0, class x1, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0, x1, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F1, x0, x1, xs...),
      xs...
    );
  };

  template<class C, class F0>
  struct partial_tee_impl<C, F0>
  {
    template<class x0, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0, xs...),
      xs...
    );
  };

  template<class C>
  struct partial_tee_impl<C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };
} // namespace jln::mp
/// \endcond
