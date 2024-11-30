// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/rotate.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class... Fs>
    struct partial_tee0_xs_impl;

    struct partial_tee_xs_impl;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions each taking the parameter corresponding to its position,
  /// except the last one taking zero to all remaining parameters.
  /// \semantics
  ///   \code
  ///   partial_tee_xs<F,G,H,C>::f<a> == /* error */
  ///   partial_tee_xs<F,G,H,C>::f<a,b> == C::f<F::f<a,b>, G::f<a,b>, H::f<>>
  ///   partial_tee_xs<F,G,H,C>::f<a,b,c,d> == C::f<F::f<a,b,c,d>, G::f<a,b,c,d>, H::f<c,d>>
  ///   partial_tee_xs<C>::f<> == C::f<>
  ///   partial_tee_xs<C>::f<a> == /* error */
  ///   \endcode
  /// \treturn \value
  /// \see partial_tee0_xs, partial_tee, partial_transform, tee, each
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct partial_tee_xs
  {
    template<class... xs>
    using f;
  };
#else
  template<class... Fs>
  struct partial_tee_xs
  : detail::rotate_impl<sizeof...(Fs)-2>
  ::template f<sizeof...(Fs)-2, detail::partial_tee_xs_impl, Fs...>
  {};

  template<class C>
  struct partial_tee_xs<C>
  {
    template<class... xs>
    using f = typename conditional_c<JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs))>
      ::template f<C, void>
      ::template f<>;
  };
#endif

  /// Invokes multiple functions each taking the parameter corresponding to its position
  /// (or without parameter whether it does not exist),
  /// except the last one taking zero to all remaining parameters.
  /// \semantics
  ///   \code
  ///   partial_tee0_xs<F,G,H,C>::f<a> == C::f<F::f<a>, G::f<>, H::f<>>
  ///   partial_tee0_xs<F,G,H,C>::f<a,b> == C::f<F::f<a,b>, G::f<a,b>, H::f<>>
  ///   partial_tee0_xs<F,G,H,C>::f<a,b,c,d> == C::f<F::f<a,b,c,d>, G::f<a,b,c,d>, H::f<c,d>>
  ///   partial_tee0_xs<C>::f<> == C::f<>
  ///   partial_tee0_xs<C>::f<a> == /* error */
  ///   \endcode
  /// \treturn \value
  /// \see partial_tee_xs, partial_tee0, partial_transform, tee, each
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct partial_tee0_xs
  {
    template<class... xs>
    using f;
  };
#else
  template<class... Fs>
  struct partial_tee0_xs
  : detail::rotate_impl<sizeof...(Fs)-2>
  ::template f<sizeof...(Fs)-2, lift<detail::partial_tee0_xs_impl>, Fs...>
  {};

  template<class C>
  struct partial_tee0_xs<C> : partial_tee_xs<C>
  {};
#endif
}


#include <jln/mp/list/take_front.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/functional/partial_tee.hpp>

/// \cond
namespace jln::mp::detail
{
  constexpr int partial_tee_xs_selector(std::size_t nf, std::size_t nx)
  {
    nf -= 2;
    return nf == nx ? 1
         : nf < nx ? 2
         : 3;
  }

  template<int, class C, class... Fs>
  struct partial_tee_xs_select;

  // each (sizeof...(Fs) == sizeof...(xs))
  template<class F, class C, class... Fs>
  struct partial_tee_xs_select<1, F, C, Fs...>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, Fs, xs...)...,
      JLN_MP_CALL_TRACE_0_ARG(F)
    );
  };

  // sizeof...(Fs) + 1 < sizeof...(xs)
  template<class F, class C, class... Fs>
  struct partial_tee_xs_select<2, F, C, Fs...>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, Fs, xs...)...,
      typename drop_front_impl<(sizeof...(xs) & 0) + sizeof...(Fs)>
      ::template f<sizeof...(Fs), JLN_MP_TRACE_F(F), xs...>
    );
  };

  // sizeof...(Fs) + 1 > sizeof...(xs)
  template<class F, class C, class... Fs>
  struct partial_tee_xs_select<3, F, C, Fs...>
    : partial_tee_select<2, C, Fs..., F>
  {};

  template<class... Fs>
  struct partial_tee0_xs_impl
  {
    template<class... xs>
    using f = typename partial_tee_xs_select<
      partial_tee_xs_selector(sizeof...(Fs), sizeof...(xs)),
      Fs...
    >::template f<xs...>;
  };

  struct partial_tee_xs_impl
  {
    template<class... Fs>
    using f = partial_tee_xs_select<2, Fs...>;
  };
}
/// \endcond
