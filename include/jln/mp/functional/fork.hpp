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
    struct _fork;
  }
  /// \endcond

  /// \ingroup functional

  /// Invoke multiple functions passing all parameters to each.
  /// \pre sizeof...(Fs) >= 1
  /// \semantics
  ///   \code
  ///   fork\<Fs...,C\>::f\<xs...\> == C::f\<Fs::f\<xs...\>...\>
  ///   \endcode
  /// \return \value
  /// \see each
  /// \see partial
  template <class... Fs>
  struct fork
  : rotate<number<-1>, cfe<detail::_fork>>
  ::template f<Fs...>
  {};

  /// \cond
  template <class F, class C>
  struct fork<F, C>
  {
    template<class... xs>
    using f = unary_compose_call<C, F, xs...>;
  };

  template <class F0, class F1, class C>
  struct fork<F0, F1, C>
  {
    template<class... xs>
    using f = binary_compose_call<C, F0, F1, xs...>;
  };

  template <class F0, class F1, class F2, class C>
  struct fork<F0, F1, F2, C>
  {
    template<class... xs>
    using f = ternary_compose_call<C, F0, F1, F2, xs...>;
  };
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template <class C, class... Fs>
  struct _fork
  {
    template <class... xs>
    using f = typename C::template f<call<Fs, xs...>...>;
  };
} // namespace jln::mp
/// \endcond
