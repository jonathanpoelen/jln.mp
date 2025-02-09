// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/take_front.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Removes \c N elements from the end of a \sequence.
  /// \pre `0 <= N <= sizeof...(xs)`
  /// \treturn \sequence
  /// \see drop_back_max, drop_front, take_front, take_back, drop_while
  template<unsigned N, class C = listify>
  struct drop_back_c
  {
    template<class... xs>
    using f = typename detail::take_front_impl<sizeof...(xs) - N>
      ::template f<sizeof...(xs) - N, JLN_MP_TRACE_F(C)::template f, xs...>;
  };

  /// Removes at most \c N elements from the end of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  /// \see drop_back, drop_front, drop_while
  template<unsigned N, class C = listify>
  struct drop_back_max_c
  {
    template<class... xs>
    using f = typename detail::take_front_impl<
        sizeof...(xs) <= N ? 0 : sizeof...(xs) - N
      >
      ::template f<
        sizeof...(xs) <= N ? 0 : sizeof...(xs) - N,
        JLN_MP_TRACE_F(C)::template f,
        xs...
      >;
  };

  template<class N, class C = listify>
  using drop_back = drop_back_c<N::value, C>;

  template<class N, class C = listify>
  using drop_back_max = drop_back_max_c<N::value, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using drop_back = typename detail::_unpack<mp::drop_back<N, C>, L>::type;

    template<class L, int_t n, class C = mp::listify>
    using drop_back_c = typename detail::_unpack<mp::drop_back_c<n, C>, L>::type;

    template<class L, class N, class C = mp::listify>
    using drop_back_max = typename detail::_unpack<mp::drop_back_max<N, C>, L>::type;

    template<class L, int_t n, class C = mp::listify>
    using drop_back_max_c = typename detail::_unpack<mp::drop_back_max_c<n, C>, L>::type;
  }

  /// \cond
  #if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_DEBUG
  template<unsigned N, template<class...> class C>
  struct drop_back_c<N, lift<C>>
  {
    template<class... xs>
    using f = typename detail::take_front_impl<sizeof...(xs) - N>
      ::template f<sizeof...(xs) - N, C, xs...>;
  };

  template<template<class...> class C>
  struct drop_back_c<0, lift<C>>
    : detail::call_trace_xs<lift<C>>
  {};

  template<unsigned N, template<class...> class C>
  struct drop_back_max_c<N, lift<C>>
  {
    template<class... xs>
    using f = typename detail::take_front_impl<
        sizeof...(xs) <= N ? 0 : sizeof...(xs) - N
      >
      ::template f<
        sizeof...(xs) <= N ? 0 : sizeof...(xs) - N,
        C, xs...
      >;
  };

  template<template<class...> class C>
  struct drop_back_max_c<0, lift<C>>
    : detail::call_trace_xs<lift<C>>
  {};
  #endif

  template<class C>
  struct drop_back_c<0, C>
    : detail::call_trace_xs<C>
  {};

  template<class C>
  struct drop_back_max_c<0, C>
    : detail::call_trace_xs<C>
  {};
  /// \endcond
}
