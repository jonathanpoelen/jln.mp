// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/utility/conditional.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/list/join.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned>
    struct take_front_impl;
  }
  /// \endcond

  /// \ingroup list

  /// Extracts \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N <= sizeof...(xs)`
  /// \treturn \sequence
  /// \see take_front_max, take_back, drop_front, drop_back, take_while
  template<unsigned N, class C = listify>
  struct take_front_c
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
#else
    template<class _0, class _1, class _2, class _3, class _4, class _5,
             class _6, class _7, class _8, class... xs>
    using f = typename detail::_join_select<2>::f<
      JLN_MP_TRACE_F(C)::template f,
      list<_0, _1, _2, _3, _4, _5, _6, _7, _8>,
      typename JLN_MP_CALLER_TRACE_XS(xs, detail::take_front_impl<N-9>)
        ::template f<N-9, list<>, xs...>
    >::type;
#endif
  };

  /// Extracts at most \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  /// \see take_front, take_back, take_while
  template<unsigned N, class C = listify>
  struct take_front_max_c
  {
    template<class... xs>
    using f = typename conditional_c<sizeof...(xs) <= N>
      ::template f<JLN_MP_TRACE_F(C), take_front_c<N, C>>
      ::template f<xs...>;
  };

  template<class N, class C = listify>
  using take_front = take_front_c<N::value, C>;

  template<class N, class C = listify>
  using take_front_max = take_front_max_c<N::value, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using take_front = unpack<L, mp::take_front<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using take_front_c = unpack<L, mp::take_front_c<n, C>>;

    template<class L, class N, class C = mp::listify>
    using take_front_max = unpack<L, mp::take_front_max<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using take_front_max_c = unpack<L, mp::take_front_max_c<n, C>>;
  }


  /// \cond
  template<class C>
  struct take_front_c<0, C>
    : detail::call_trace_xs_0<C>
  {};

  template<class C>
  struct take_front_max_c<0, C>
    : detail::call_trace_xs_0<C>
  {};

  #define JLN_MP_TAKE_FRONT(n, mp_xs, mp_rxs, mp_dup)               \
    template<class C>                                               \
    struct take_front_c<n, C>                                       \
    {                                                               \
      template<mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA), class... xs> \
      using f = JLN_MP_DCALL_TRACE_XS(xs, C,                        \
        mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA));               \
    };                                                              \
                                                                    \
    template<>                                                      \
    struct take_front_c<n, listify>                                 \
    {                                                               \
      template<mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA), class... xs> \
      using f = list<mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>;  \
    };

  JLN_MP_GEN_XS_1_TO_8_INCLUDED(JLN_MP_TAKE_FRONT)
  #undef JLN_MP_TAKE_FRONT

  #if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
  template<unsigned N, template<class...> class C>
  struct take_front_c<N, lift<C>>
  {
    template<class _0, class _1, class _2, class _3, class _4, class _5,
             class _6, class _7, class _8, class... xs>
    using f = typename detail::_join_select<2>::f<
      C,
      list<_0, _1, _2, _3, _4, _5, _6, _7, _8>,
      typename JLN_MP_CALLER_TRACE_XS(xs, detail::take_front_impl<N-9>)
        ::template f<N-9, list<>, xs...>
    >::type;
  };

  template<template<class...> class C>
  struct take_front_c<0, lift<C>>
    : detail::call_trace_xs_0<lift<C>>
  {};

  #define JLN_MP_TAKE_FRONT(n, mp_xs, mp_rxs, mp_dup)               \
    template<template<class...> class C>                            \
    struct take_front_c<n, lift<C>>                                 \
    {                                                               \
      template<mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA), class... xs> \
      using f = JLN_MP_DCALLF_XS(xs, C,                             \
        mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA));               \
    };

  JLN_MP_GEN_XS_1_TO_8_INCLUDED(JLN_MP_TAKE_FRONT)
  #undef JLN_MP_TAKE_FRONT
  #endif
  /// \endcond
}


/// \cond
namespace jln::mp::detail
{
  template<unsigned n>
  struct take_front_impl : take_front_impl<
      n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

  template<>
  struct take_front_impl<0>
  {
    template<unsigned size, class L, class... xs>
    using f = L;
  };

#define JLN_MP_TAKE_IMPL(n, mp_xs, mp_rxs, mp_rep)      \
  template<>                                            \
  struct take_front_impl<n>                             \
  {                                                     \
    template<unsigned size,                             \
      class L,                                          \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)            \
      class... xs>                                      \
    using f = typename _join_select<2>::f<list, L,      \
      list<mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)> \
    >::type;                                            \
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_TAKE_IMPL)

#undef JLN_MP_TAKE_IMPL

#define JLN_MP_TAKE_IMPL(n, mp_xs, mp_rxs, mp_rep)          \
  template<>                                                \
  struct take_front_impl<n>                                 \
  {                                                         \
    template<unsigned size,                                 \
      class L,                                              \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)                \
      class... xs>                                          \
    using f = typename take_front_impl<size-n>              \
      ::template f<size-n,                                  \
        typename _join_select<2>::f<list, L,                \
          list<mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)> \
        >::type,                                            \
        xs...                                               \
      >;                                                    \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_TAKE_IMPL)

#undef JLN_MP_TAKE_IMPL
}
/// \endcond
