// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/listify.hpp>

#include <cstddef>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<std::size_t n>
    struct _join_select;
  }
  /// \endcond

  /// \ingroup list

  /// Concatenates \lists.
  /// \pre \c seqs must be a \sequence of \list
  /// \treturn \sequence
  template<class C = listify>
  struct join
  {
    template<class... seqs>
    using f = typename detail::_join_select<sizeof...(seqs)>
      ::template f<JLN_MP_TRACE_F(C)::template f, seqs...>::type;
  };

  /// \cond
  #if ! JLN_MP_OPTIMIZED_ALIAS
  template<template<class...> class C>
  struct join<lift<C>>
  {
    template<class... seqs>
    using f = typename detail::_join_select<sizeof...(seqs)>
      ::template f<C, seqs...>::type;
  };
  #endif
  /// \endcond

  namespace emp
  {
    template<class... seqs>
    using join = typename mp::join<>::template f<seqs...>;
  }
}

#include <jln/mp/detail/sequence.hpp>
#include <jln/mp/detail/compiler.hpp>

/// \cond
namespace jln::mp::detail
{
  template<std::size_t n>
  struct _join_select : _join_select<
      n <= 2 ? 2
    : n <= 8 ? 8
    : n <= 16 ? 16
    : n <= 64 ? 64
    : n <= 256 ? 256
    : 512
  >
  {};

  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_MSVC_IGNORE(4348)

#define JLN_MP_JOIN_SELECT(n, mp_xs, mp_rxs, _)   \
  template<>                                      \
  struct _join_select<n>                          \
  {                                               \
    template<template<class...> class F,          \
      mp_xs(class, = list<>, JLN_MP_COMMA)>       \
    struct f;                                     \
                                                  \
    template<template<class...> class F,          \
      mp_xs(class..., JLN_MP_NIL, JLN_MP_COMMA)>  \
    struct f<F, mp_xs(list<, ...>, JLN_MP_COMMA)> \
    {                                             \
      using type = F<                             \
        mp_xs(JLN_MP_NIL, ..., JLN_MP_COMMA)>;    \
    };                                            \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_JOIN_SELECT)
  JLN_MP_JOIN_SELECT(2, JLN_MP_XS_2, _, _)

#undef JLN_MP_JOIN_SELECT

  template<>
  struct _join_select<512>
  {
    template<template<class...> class F,
      JLN_MP_XS_512(class, = list<>, JLN_MP_COMMA),
      class... tail>
    struct f;

    template<template<class...> class F,
      JLN_MP_XS_512(class..., JLN_MP_NIL, JLN_MP_COMMA),
      class... tail>
    struct f<F, JLN_MP_XS_512(list<, ...>, JLN_MP_COMMA), tail...>
    : _join_select<2>::f<F,
        list<JLN_MP_XS_512(JLN_MP_NIL, ..., JLN_MP_COMMA)>,
        typename _join_select<sizeof...(tail)>::template f<list, tail...>::type>
    {};
  };

  JLN_MP_DIAGNOSTIC_POP()

} // namespace jln::mp::detail
/// \endcond
