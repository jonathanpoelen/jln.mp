#pragma once

#include "../algorithm/rotate.hpp"
#include "../number/number.hpp"
#include "function.hpp"
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
  /// \pre sizeof...(Fs) >= 1
  /// \pre sizeof...(xs) == sizeof...(Fs) - 1
  /// \semantics
  ///   \code
  ///   each\<Fs...,C\>::f\<xs...\> == C::f\<Fs::f\<xs\>...\>
  ///   \endcode
  /// \treturn \value
  /// \see fork
  /// \see partial
  template <class... Fs>
  struct each
  : rotate<number<-1>, cfe<detail::_each>>
  ::template f<Fs...>
  {};

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
