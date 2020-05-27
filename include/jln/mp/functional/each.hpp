#pragma once

#include "../algorithm/rotate.hpp"
#include "../number/number.hpp"
#include "lift.hpp"
#include "call.hpp"

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template <class C, class... Fs>
    struct _each;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions each taking the parameter corresponding to its position.
  /// \treturn \value
  /// \see tee, partial
#ifdef JLN_MP_DOXYGENATING
  template <class... Fs, class C>
  struct each
  {
    template<class... xs>
    using f = C::f<Fs::f<xs>...>;
  };
#else
  template <class... Fs>
  struct each
  : rotate<number<-1>, lift<detail::_each>>
  ::template f<Fs...>
  {};
#endif

  /// \cond
  template <class C>
  struct each<C> : detail::_each<C>
  {};

  template <class F, class C>
  struct each<F, C> : detail::_each<C, F>
  {};

  template <class F0, class F1, class C>
  struct each<F0, F1, C> : detail::_each<C, F0, F1>
  {};

  template <class F0, class F1, class F2, class C>
  struct each<F0, F1, F2, C> : detail::_each<C, F0, F1, F2>
  {};
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template <class C, class... Fs>
  struct _each
  {
    template <class... xs>
    using f = call<C, call<Fs, xs>...>;
  };
} // namespace jln::mp
/// \endcond
