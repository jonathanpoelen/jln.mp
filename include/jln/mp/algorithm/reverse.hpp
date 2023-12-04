// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/detail/sequence.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned>
    struct reverse_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Reverses the order of the elements of a \sequence.
  /// \treturn \sequence
  template<class C = listify>
  struct reverse
  {
    template<class... xs>
    using f = typename detail::reverse_impl<sizeof...(xs)>
      ::template f<C, sizeof...(xs), xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using reverse = unpack<L, mp::reverse<C>>;
  }
}


#include <jln/mp/list/join.hpp>
#include <jln/mp/utility/conditional.hpp>

/// \cond
namespace jln::mp::detail
{
  template<unsigned n>
  struct reverse_impl2 : reverse_impl2<
      n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

  template<unsigned n>
  struct reverse_impl : reverse_impl2<
      n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

#define JLN_MP_REVERSE_IMPL(n, mp_xs, mp_rxs, mp_rep)    \
  template<>                                             \
  struct reverse_impl2<n>                                \
  {                                                      \
    template<class C, std::size_t count                  \
      mp_xs(JLN_MP_COMMA class, JLN_MP_NIL, JLN_MP_NIL), \
      class... xs>                                       \
    using f = typename reverse<join<C>>                  \
      ::template f<xs..., list<                          \
        mp_rxs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>>;  \
  };                                                     \
  template<>                                             \
  struct reverse_impl<n>                                 \
  {                                                      \
    template<class C, std::size_t count                  \
      mp_xs(JLN_MP_COMMA class, JLN_MP_NIL, JLN_MP_NIL), \
      class... xs>                                       \
    using f = JLN_MP_CALL_TRACE(C,                       \
      mp_rxs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA));     \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_MP_REVERSE_IMPL)

#undef JLN_MP_REVERSE_IMPL

#define JLN_MP_REVERSE_IMPL(n, mp_xs, mp_rxs, mp_rep) \
  template<>                                          \
  struct reverse_impl2<n>                             \
  {                                                   \
    template<class C, std::size_t count,              \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),         \
      class... xs>                                    \
    using f = typename reverse_impl2<                 \
      count-n                                         \
    >::template f<C, count-n, xs..., list<            \
      mp_rxs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>>; \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_REVERSE_IMPL)

#undef JLN_MP_REVERSE_IMPL
}
/// \endcond
