// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/rotate.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    struct partial_transform_impl;

    template<class C, class... Fs>
    struct partial_transform0_impl;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions each taking the parameter corresponding to its position,
  /// then calls \c C with the results and the rest of the parameters.
  /// \semantics
  ///   \code
  ///   partial_transform<F,G,C>::f<a> == /* error */
  ///   partial_transform<F,G,C>::f<a,b,c,d> == C::f<F::f<a>, G::f<b>, c, d>
  ///   \endcode
  /// \treturn \value
  /// \see partial_transform0, partial_transform_xs, partial_tee, each, tee
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct partial_transform
  {
    template<class... xs>
    using f;
  };
#else
  template<class... Fs>
  struct partial_transform
  : detail::rotate_impl<sizeof...(Fs)-1>
  ::template f<sizeof...(Fs)-1, detail::partial_transform_impl, Fs...>
  {};
#endif

  /// Invokes multiple functions each taking the parameter corresponding to its position
  /// (or without parameter whether it does not exist),
  /// then calls \c C with the results and the rest of the parameters.
  /// \semantics
  ///   \code
  ///   partial_transform0<F,G,C>::f<a> == C::f<F::f<a>, G::f<>>
  ///   partial_transform0<F,G,C>::f<a,b,c,d> == C::f<F::f<a>, G::f<b>, c, d>
  ///   \endcode
  /// \treturn \value
  /// \see partial_transform, partial_transform_xs, partial_tee, each, tee
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct partial_transform0
  {
    template<class... xs>
    using f;
  };
#else
  template<class... Fs>
  struct partial_transform0
  : detail::rotate_impl<sizeof...(Fs)-1>
  ::template f<sizeof...(Fs)-1, lift<detail::partial_transform0_impl>, Fs...>
  {};
#endif
}

#include <jln/mp/list/take_front.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/functional/each.hpp>
#include <jln/mp/functional/bind_front.hpp>

/// \cond
namespace jln::mp::detail
{
  constexpr int partial_transform_selector(std::size_t nf, std::size_t nx)
  {
    return nf < nx ? 1 : nf > nx ? 2 : 0;
  }

  template<int, class C, class... Fs>
  struct partial_transform_select;

  // each (sizeof...(Fs) == sizeof...(xs))
  template<class C, class... Fs>
  struct partial_transform_select<0, C, Fs...>
  : _each<C, Fs...>
  {};

  template<class... Fs>
  struct partial_transform_prefix
  {
    template<class C, class... xs>
    using f = bind_front<C, typename JLN_MP_TRACE_F(Fs)::template f<xs>...>;
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class... Fs>
  struct partial_transform_select<1, C, Fs...>
  {
    template<class... xs>
    using f = typename drop_front_impl<(sizeof...(xs) & 0) + sizeof...(Fs)>
      ::template f<
        sizeof...(Fs),
        take_front_impl<sizeof...(Fs) + 1 + (sizeof...(xs) & 0)>
        ::template f<
          sizeof...(Fs) + 1,
          partial_transform_prefix<Fs...>::template f,
          C,
          xs...
        >::template f,
        xs...
      >;
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class F0, class F1, class F2, class F3>
  struct partial_transform_select<1, C, F0, F1, F2, F3>
  {
    template<class x0, class x1, class x2, class x3, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0),
      JLN_MP_DCALL_TRACE_XS(xs, F1, x1),
      JLN_MP_DCALL_TRACE_XS(xs, F2, x2),
      JLN_MP_DCALL_TRACE_XS(xs, F3, x3),
      xs...
    );
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class F3>
  struct partial_transform_select<1, C, identity, identity, identity, F3>
  {
    template<class x0, class x1, class x2, class x3, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      x0,
      x1,
      x2,
      JLN_MP_DCALL_TRACE_XS(xs, F3, x3),
      xs...
    );
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class F0, class F1, class F2>
  struct partial_transform_select<1, C, F0, F1, F2>
  {
    template<class x0, class x1, class x2, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0),
      JLN_MP_DCALL_TRACE_XS(xs, F1, x1),
      JLN_MP_DCALL_TRACE_XS(xs, F2, x2),
      xs...
    );
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class F2>
  struct partial_transform_select<1, C, identity, identity, F2>
  {
    template<class x0, class x1, class x2, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      x0,
      x1,
      JLN_MP_DCALL_TRACE_XS(xs, F2, x2),
      xs...
    );
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class F0, class F1>
  struct partial_transform_select<1, C, F0, F1>
  {
    template<class x0, class x1, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0),
      JLN_MP_DCALL_TRACE_XS(xs, F1, x1),
      xs...
    );
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class F1>
  struct partial_transform_select<1, C, identity, F1>
  {
    template<class x0, class x1, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      x0,
      JLN_MP_DCALL_TRACE_XS(xs, F1, x1),
      xs...
    );
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class F0>
  struct partial_transform_select<1, C, F0>
  {
    template<class x0, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0),
      xs...
    );
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C>
  struct partial_transform_select<1, C> : detail::call_trace_xs<C>
  {};

  template<class... Fs>
  struct partial_transform_suffix
  {
    template<class C>
    using f = JLN_MP_CALL_TRACE(C, typename JLN_MP_TRACE_F(Fs)::template f<>...);
  };

  // sizeof...(Fs) > sizeof...(xs)
  template<class C, class... Fs>
  struct partial_transform_select<2, C, Fs...>
  {
    template<class... xs>
    using f = typename drop_front_impl<sizeof...(xs)>
      ::template f<sizeof...(xs), partial_transform_suffix, Fs...>
      ::template f<
        typename take_front_impl<sizeof...(xs)>
        ::template f<sizeof...(xs), partial_transform_prefix, Fs...>
        ::template f<C, xs...>
      >;
  };

  template<class C, class... Fs>
  struct partial_transform0_impl
  {
    template<class... xs>
    using f = typename partial_transform_select<
      partial_transform_selector(sizeof...(Fs), sizeof...(xs)),
      C,
      Fs...
    >::template f<xs...>;
  };

  struct partial_transform_impl
  {
    template<class... Fs>
    using f = partial_transform_select<1, Fs...>;
  };
}
/// \endcond
