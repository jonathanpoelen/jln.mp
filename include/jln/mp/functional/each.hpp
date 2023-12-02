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
    struct _each;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions each taking the parameter corresponding to its position.
  /// \treturn \value
  /// \see tee, partial
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct each
  {
    template<class... xs>
    using f = C::f<Fs::f<xs>...>;
  };
#else
  template<class... Fs>
  struct each
  : detail::rotate_impl<sizeof...(Fs)-1>
  ::template f<sizeof...(Fs)-1, lift<detail::_each>, Fs...>
  {};
#endif
}

/// \cond
namespace jln::mp::detail
{
  template<class C, class... Fs>
  struct _each
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, typename JLN_MP_TRACE_F(Fs)::template f<xs>...);
  };
} // namespace jln::mp
/// \endcond
