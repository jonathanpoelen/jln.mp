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
    template <class C, class... Fs>
    struct _tee;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions passing all parameters to each.
  /// \treturn \value
  /// \see each, partial
#ifdef JLN_MP_DOXYGENATING
  template <class... Fs, class C>
  struct tee
  {
    template<class... xs>
    using f = C::f<Fs::f<xs...>...>;
  };
#else
  template <class... Fs>
  struct tee
  : rotate<number<-1>, lift<detail::_tee>>
  ::template f<Fs...>
  {};
#endif

  /// \cond
  template <class F, class C>
  struct tee<F, C>
  {
    template<class... xs>
    using f = unary_compose_call<C, F, xs...>;
  };

  template <class F0, class F1, class C>
  struct tee<F0, F1, C>
  {
    template<class... xs>
    using f = binary_compose_call<C, F0, F1, xs...>;
  };

  template <class F0, class F1, class F2, class C>
  struct tee<F0, F1, F2, C>
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
  struct _tee
  {
    template <class... xs>
    using f = typename C::template f<call<Fs, xs...>...>;
  };
} // namespace jln::mp
/// \endcond
