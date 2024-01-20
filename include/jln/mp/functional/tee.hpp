// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/lift.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, class... Fs>
    struct _tee;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions passing all parameters to each.
  /// \treturn \value
  /// \see each, partial
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct tee
  {
    template<class... xs>
    using f = C::f<Fs::f<xs...>...>;
  };
#else
  template<class... Fs>
  struct tee
  : detail::rotate_impl<sizeof...(Fs)-1>
  ::template f<sizeof...(Fs)-1, lift<detail::_tee>, Fs...>
  {};
#endif

  /// \cond
  template<class C>
  struct tee<C> : detail::call_trace_xs_0<C>
  {};

  template<class F, class C>
  struct tee<F, C>
  {
    template<class... xs>
    using f = typename JLN_MP_TRACE_F(C)::template f<
      JLN_MP_DCALL_TRACE_XS(xs, F, xs...)
    >;
  };

  template<class F0, class F1, class C>
  struct tee<F0, F1, C>
  {
    template<class... xs>
    using f = typename JLN_MP_TRACE_F(C)::template f<
      JLN_MP_DCALL_TRACE_XS(xs, F0, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F1, xs...)
    >;
  };

  template<class F0, class F1, class F2, class C>
  struct tee<F0, F1, F2, C>
  {
    template<class... xs>
    using f = typename JLN_MP_TRACE_F(C)::template f<
      JLN_MP_DCALL_TRACE_XS(xs, F0, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F1, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F2, xs...)
    >;
  };
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template<class C, class... Fs>
  struct _tee
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, JLN_MP_DCALL_TRACE_XS(xs, Fs, xs...)...);
  };

  template<class C>
  struct optimize_tee
  {
    using type = C;
  };

  template<class C>
  struct optimize_tee<tee<C, identity>>
    : optimize_tee<C>
  {};

  template<class C>
  using optimize_tee_t = typename optimize_tee<C>::type;
} // namespace jln::mp
/// \endcond
