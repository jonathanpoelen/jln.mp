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
    template <class, class...>
    struct _partial;

    template <class, class, class...>
    struct _partial_eager;
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
  /// \see each, tee, partial_eager
#ifdef JLN_MP_DOXYGENATING
  template <class... Fs, class C>
  struct partial
  {
    template<class... xs>
    using f = /* unspecified */;
  };
#else
  template <class... Fs>
  struct partial
  : rotate<number<-1>, lift<detail::_partial>>
  ::template f<Fs...>
  {};
#endif

  /// Invoke multiple functions each taking the parameter corresponding to its position
  /// (the last function takes the remaining parameters or 0)
  /// then calls \c C with the results.
  /// \pre `sizeof...(xs) + 1 >= sizeof...(Fs)`
  /// \semantics
  ///   \code
  ///   partial_eagerF,G,C::fa,b,c,d == CFa, Gb, c, d
  ///   partial_eagerF,G,C::fa == CFa, G
  ///   \endcode
  /// \treturn \value
  /// \see each, tee, partial
#ifdef JLN_MP_DOXYGENATING
  template <class... Fs, class C>
  struct partial_eager
  {
    template<class... xs>
    using f = /* unspecified */;
  };
#else
  template <class... Fs>
  struct partial_eager
  : rotate<number<-2>, lift<detail::_partial_eager>>
  ::template f<Fs...>::type
  {};
#endif

  /// \cond
  template <class C>
  struct partial<C>
  {
    template <class... xs>
    using f = call<C, xs...>;
  };

  template <class F, class C>
  struct partial<F, C>
  {
    template <class x, class... xs>
    using f = call<C, call<F, x>, xs...>;
  };

  template <class F0, class F1, class C>
  struct partial<F0, F1, C>
  {
    template <class x0, class x1, class... xs>
    using f = call<C, call<F0, x0>, call<F1, x1>, xs...>;
  };

  template <class F0, class F1, class F2, class C>
  struct partial<F0, F1, F2, C>
  {
    template <class x0, class x1, class x2, class... xs>
    using f = call<C, call<F0, x0>, call<F1, x1>, call<F2, x2>, xs...>;
  };

  template <class C>
  struct partial_eager<C>
  {
    template <class... xs>
    using f = call<C, xs...>;
  };

  template <class F, class C>
  struct partial_eager<F, C>
  {
    template <class... xs>
    using f = unary_compose_call<C, F, xs...>;
  };

  template <class F0, class F1, class C>
  struct partial_eager<F0, F1, C>
  {
    template <class x0, class... xs>
    using f = JLN_MP_DCALL_XS(xs,
      C, call<F0, x0>, call<F1, xs...>);
  };

  template <class F0, class F1, class F2, class C>
  struct partial_eager<F0, F1, F2, C>
  {
    template <class x0, class x1, class... xs>
    using f = JLN_MP_DCALL_XS(xs,
      C, call<F0, x0>, call<F1, x1>, call<F2, xs...>);
  };
  /// \endcond
}

#include "../algorithm/make_int_sequence.hpp"
#include "../algorithm/transform.hpp"
#include "../utility/always.hpp"
#include "../list/join.hpp"
#include "../list/take.hpp"
#include "../list/drop.hpp"
#include "each.hpp"
#include "tee.hpp"

/// \cond
namespace jln::mp::detail
{
  template <class C, class... Fs>
  struct _partial
  {
    template<class... xs>
    using f = typename _join_select<2>::f<
      lift<_each>,
      list<C, Fs...>,
      emp::make_int_sequence_c<sizeof...(xs) - sizeof...(Fs), transform<always<identity>>>
    >::type::template f<xs...>;
  };

  template <class Flast, class C, class... Fs>
  struct _partial_eager
  {
    using type = tee<
      take_c<sizeof...(Fs), _each<listify, Fs...>>,
      drop_c<sizeof...(Fs), tee<Flast, listify>>,
      join<C>
    >;
  };
} // namespace jln::mp
/// \endcond
