// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/rotate.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    struct partial_tee_impl;

    template<class C, class... Fs>
    struct partial_tee0_impl;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions passing all parameters to each
  /// then calls \c C with the results and parameters without the first `sizeof...(Fs)`.
  /// \semantics
  ///   \code
  ///   partial_tee<F,G,C>::f<a> == /* error */
  ///   partial_tee<F,G,C>::f<a,b,c,d> == C::f<F::f<a,b,c,d>, G::f<a,b,c,d>, c, d>
  ///   \endcode
  /// \treturn \value
  /// \see partial_tee0, partial_tee_xs, partial_transform, each, tee
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
  ::template f<sizeof...(Fs)-1, detail::partial_tee_impl, Fs...>
  {};
#endif

  /// Invokes multiple functions passing all parameters to each
  /// (or without parameter whether it does not exist),
  /// then calls \c C with the results and parameters without the first `sizeof...(Fs)`.
  /// \semantics
  ///   \code
  ///   partial_tee0<F,G,C>::f<a> == C::f<F::f<a>, G::f<>>
  ///   partial_tee0<F,G,C>::f<a,b> == C::f<F::f<a,b>, G::f<a,b>>
  ///   partial_tee0<F,G,C>::f<a,b,c,d> == C::f<F::f<a,b,c,d>, G::f<a,b,c,d>, c, d>
  ///   \endcode
  /// \treturn \value
  /// \see partial_tee, partial_tee0_xs, partial_transform, each, tee
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct partial_tee0
  {
    template<class... xs>
    using f;
  };
#else
  template<class... Fs>
  struct partial_tee0
  : detail::rotate_impl<sizeof...(Fs)-1>
  ::template f<sizeof...(Fs)-1, lift<detail::partial_tee0_impl>, Fs...>
  {};
#endif
}

#include <jln/mp/list/take_front.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/functional/tee.hpp>
#include <jln/mp/functional/bind_front.hpp>
#include <jln/mp/functional/partial_transform.hpp>

/// \cond
namespace jln::mp::detail
{
  template<int, class C, class... Fs>
  struct partial_tee_select;

  // tee (sizeof...(Fs) == sizeof...(xs))
  template<class C, class... Fs>
  struct partial_tee_select<0, C, Fs...>
  : _tee<C, Fs...>
  {};

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class... Fs>
  struct partial_tee_select<1, C, Fs...>
  {
    template<class... xs>
    using f = typename drop_front_impl<
      (sizeof...(xs) & 0) + sizeof...(Fs)
    >::template f<
      sizeof...(Fs),
      bind_front<C, JLN_MP_DCALL_TRACE_XS(xs, Fs, xs...)...>,
      xs...
    >;
  };

  template<class C, class F0, class F1, class F2, class F3>
  struct partial_tee_select<1, C, F0, F1, F2, F3>
  {
    template<class x0, class x1, class x2, class x3, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0, x1, x2, x3, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F1, x0, x1, x2, x3, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F2, x0, x1, x2, x3, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F3, x0, x1, x2, x3, xs...),
      xs...
    );
  };

  template<class C, class F0, class F1, class F2>
  struct partial_tee_select<1, C, F0, F1, F2>
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
  struct partial_tee_select<1, C, F0, F1>
  {
    template<class x0, class x1, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0, x1, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F1, x0, x1, xs...),
      xs...
    );
  };

  template<class C, class F0>
  struct partial_tee_select<1, C, F0>
  {
    template<class x0, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0, xs...),
      xs...
    );
  };

  template<class C>
  struct partial_tee_select<1, C> : detail::call_trace_xs<C>
  {};

  template<class... Fs>
  struct partial_tee_prefix
  {
    template<class C, class... xs>
    using f = bind_front<C, JLN_MP_DCALL_TRACE_XS(xs, Fs, xs...)...>;
  };

  // sizeof...(Fs) > sizeof...(xs)
  template<class C, class... Fs>
  struct partial_tee_select<2, C, Fs...>
  {
    template<class... xs>
    using f = typename drop_front_impl<sizeof...(xs)>
      ::template f<sizeof...(xs), lift<partial_transform_suffix>, Fs...>
      ::template f<
        typename take_front_impl<sizeof...(xs)>
        ::template f<sizeof...(xs), partial_tee_prefix, Fs...>
        ::template f<C, xs...>
      >;
  };

  template<class C, class... Fs>
  struct partial_tee0_impl
  {
    template<class... xs>
    using f = typename partial_tee_select<
      partial_transform_selector(sizeof...(Fs), sizeof...(xs)),
      C,
      Fs...
    >::template f<xs...>;
  };

  struct partial_tee_impl
  {
    template<class... Fs>
    using f = partial_tee_select<1, Fs...>;
  };
} // namespace jln::mp
/// \endcond
