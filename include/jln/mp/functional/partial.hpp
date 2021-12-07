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
    template <class, class...>
    struct _partial;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions each taking the parameter corresponding to its position
  /// then calls \c C with the results and the rest of the parameters.
  /// \pre `sizeof...(xs) >= sizeof...(Fs)`
  /// \semantics
  ///   \code
  ///   partial<F,G,C>::f<a,b,c,d> == C::f<F::f<a>, G::f<b>, c, d>
  ///   \endcode
  /// \treturn \value
  /// \see each, tee, on
#ifdef JLN_MP_DOXYGENATING
  template <class... Fs, class C>
  struct partial
  {
    template<class... xs>
    using f;
  };
#else
  template <class... Fs>
  struct partial
  : rotate_c<-1, lift<detail::_partial>>
  ::template f<Fs...>
  {};
#endif

  /// \cond
  template <class C>
  struct partial<C>
  {
    template <class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };

  template <class F, class C>
  struct partial<F, C>
  {
    template <class x, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, JLN_MP_CALL_TRACE(F, x), xs...); };

  template <class F0, class F1, class C>
  struct partial<F0, F1, C>
  {
    template <class x0, class x1, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, JLN_MP_CALL_TRACE(F0, x0),
                                           JLN_MP_CALL_TRACE(F1, x1),
                                           xs...);
  };

  template <class F0, class F1, class F2, class C>
  struct partial<F0, F1, F2, C>
  {
    template <class x0, class x1, class x2, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, JLN_MP_CALL_TRACE(F0, x0),
                                           JLN_MP_CALL_TRACE(F1, x1),
                                           JLN_MP_CALL_TRACE(F2, x2),
                                           xs...);
  };
  /// \endcond
}

#include <jln/mp/list/join.hpp>
#include <jln/mp/list/take_front.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/functional/each.hpp>

/// \cond
namespace jln::mp::detail
{
  template <class C, class... Fs>
  struct _partial
  {
    template<class... xs>
    using f = typename _join_select<2>::f<
      JLN_MP_TRACE_F(C),
      typename take_front_c<sizeof...(Fs), _each<listify, Fs...>>::template f<xs...>,
      typename drop_front_c<sizeof...(Fs)>::template f<xs...>
    >::type;
  };
} // namespace jln::mp
/// \endcond
