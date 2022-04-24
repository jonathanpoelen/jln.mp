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
    struct _partial;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions each taking the parameter corresponding to its position
  /// (or without parameter whether it does not exist)
  /// then calls \c C with the results and the rest of the parameters.
  /// \semantics
  ///   \code
  ///   partial<F,G,C>::f<a> == C::f<F::f<a>, G::f<>>
  ///   partial<F,G,C>::f<a,b,c,d> == C::f<F::f<a>, G::f<b>, c, d>
  ///   \endcode
  /// \treturn \value
  /// \see each, tee, partial
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct partial
  {
    template<class... xs>
    using f;
  };
#else
  template<class... Fs>
  struct partial
  : rotate_c<-1, lift<detail::_partial>>
  ::template f<Fs...>
  {};
#endif
}

#include <jln/mp/list/join.hpp>
#include <jln/mp/list/take_front.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/functional/each.hpp>
#include <jln/mp/functional/tee.hpp>

/// \cond
namespace jln::mp::detail
{
  constexpr int on_select(std::size_t nf, std::size_t nx)
  {
    return nf < nx ? 1 : nf > nx ? 2 : 0;
  }

  template<int, class C, class... Fs>
  struct _partial_select;

  // each
  template<class C, class... Fs>
  struct _partial_select<0, C, Fs...>
  : _each<C, Fs...>
  {};

  template<class C, class... Fs>
  struct _partial_select<1, C, Fs...>
  {
    template<class... xs>
    using f = typename _join_select<2>::f<
      JLN_MP_TRACE_F(C)::template f,
      typename take_front_c<sizeof...(Fs), _each<listify, Fs...>>::template f<xs...>,
      typename drop_front_c<sizeof...(Fs)>::template f<xs...>
    >::type;
  };

  template<class C, class... Fs>
  struct _partial_select<2, C, Fs...>
  {
    template<class... xs>
    using f = typename _join_select<2>::f<
      JLN_MP_TRACE_F(C)::template f,
      typename take_front_c<sizeof...(xs)+1, lift<_each>>
        ::template f<listify, Fs...>
        ::template f<xs...>,
      typename drop_front_c<sizeof...(xs), lift<tee>>
        ::template f<Fs..., listify>
        ::template f<>
    >::type;
  };

#if ! JLN_MP_ENABLE_DEBUG
  template<template<class...> class C, class... Fs>
  struct _partial_select<1, lift<C>, Fs...>
  {
    template<class... xs>
    using f = typename _join_select<2>::f<
      C,
      typename take_front_c<sizeof...(Fs), _each<listify, Fs...>>::template f<xs...>,
      typename drop_front_c<sizeof...(Fs)>::template f<xs...>
    >::type;
  };

  template<template<class...> class C, class... Fs>
  struct _partial_select<2, lift<C>, Fs...>
  {
    template<class... xs>
    using f = typename _join_select<2>::f<
      C,
      typename take_front_c<sizeof...(xs)+1, lift<_each>>
        ::template f<listify, Fs...>
        ::template f<xs...>,
      typename drop_front_c<sizeof...(xs), lift<tee>>
        ::template f<Fs..., listify>
        ::template f<>
    >::type;
  };
#endif

  template<class C, class... Fs>
  struct _partial
  {
    template<class... xs>
    using f = typename _partial_select<on_select(sizeof...(Fs), sizeof...(xs)), C, Fs...>
      ::template f<xs...>;
  };
} // namespace jln::mp
/// \endcond
