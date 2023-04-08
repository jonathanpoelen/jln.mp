#pragma once

#include <jln/mp/algorithm/rotate.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    struct partial_each_impl;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions each taking the parameter corresponding to its position,
  /// then calls \c C with the results and the rest of the parameters.
  /// \semantics
  ///   \code
  ///   partial_each<F,G,C>::f<a> == /* error */
  ///   partial_each<F,G,C>::f<a,b,c,d> == C::f<F::f<a>, G::f<b>, c, d>
  ///   \endcode
  /// \treturn \value
  /// \see partial_tee, partial, each, tee
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct partial_each
  {
    template<class... xs>
    using f;
  };
#else
  template<class... Fs>
  struct partial_each
  : detail::rotate_impl<sizeof...(Fs)-1>
  ::template f<sizeof...(Fs)-1, detail::partial_each_impl, Fs...>
  {};
#endif
}

#include <jln/mp/functional/partial.hpp>

/// \cond
namespace jln::mp::detail
{
  struct partial_each_impl
  {
    template<class... Fs>
    using f = _partial_select<1, Fs...>;
  };
}
/// \endcond
