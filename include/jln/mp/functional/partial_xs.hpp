// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/functional/lift.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, class... Fs>
    struct partial_xs_impl;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions passing all parameters to each
  /// (or without parameter whether it does not exist),
  /// then calls \c C with the results and the rest of the parameters.
  /// \semantics
  ///   \code
  ///   partial_xs<F,G,C>::f<a> == C::f<F::f<a>, G::f<>>
  ///   partial_xs<F,G,C>::f<a,b,c,d> == C::f<F::f<a,b,c,d>, G::f<a,b,c,d>, c, d>
  ///   \endcode
  /// \treturn \value
  /// \see partial_each, partial_tee, each, tee
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct partial_xs
  {
    template<class... xs>
    using f;
  };
#else
  template<class... Fs>
  struct partial_xs
  : detail::rotate_impl<sizeof...(Fs)-1>
  ::template f<sizeof...(Fs)-1, lift<detail::partial_xs_impl>, Fs...>
  {};
#endif
}

#include <jln/mp/list/take_front.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/functional/tee.hpp>
#include <jln/mp/functional/partial.hpp>
#include <jln/mp/functional/bind_front.hpp>

/// \cond
namespace jln::mp::detail
{
  template<int, class C, class... Fs>
  struct partial_xs_select;

  // tee (sizeof...(Fs) == sizeof...(xs))
  template<class C, class... Fs>
  struct partial_xs_select<0, C, Fs...>
  : _tee<C, Fs...>
  {};

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class... Fs>
  struct partial_xs_select<1, C, Fs...>
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
  struct partial_xs_select<1, C, F0, F1, F2, F3>
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
  struct partial_xs_select<1, C, F0, F1, F2>
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
  struct partial_xs_select<1, C, F0, F1>
  {
    template<class x0, class x1, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0, x1, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F1, x0, x1, xs...),
      xs...
    );
  };

  template<class C, class F0>
  struct partial_xs_select<1, C, F0>
  {
    template<class x0, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0, xs...),
      xs...
    );
  };

  template<class C>
  struct partial_xs_select<1, C> : detail::call_trace_xs<C>
  {};

  template<class... Fs>
  struct partial_xs_prefix
  {
    template<class C, class... xs>
    using f = bind_front<C, JLN_MP_DCALL_TRACE_XS(xs, Fs, xs...)...>;
  };

  // sizeof...(Fs) > sizeof...(xs)
  template<class C, class... Fs>
  struct partial_xs_select<2, C, Fs...>
  {
    template<class... xs>
    using f = typename drop_front_c<sizeof...(xs), lift<partial_suffix>>
      ::template f<Fs...>
      ::template f<
        typename take_front_c<sizeof...(xs), lift<partial_xs_prefix>>
        ::template f<Fs...>
        ::template f<C, xs...>
      >;
  };

  template<class C, class... Fs>
  struct partial_xs_impl
  {
    template<class... xs>
    using f = typename partial_xs_select<on_select(sizeof...(Fs), sizeof...(xs)), C, Fs...>
      ::template f<xs...>;
  };
} // namespace jln::mp
/// \endcond
