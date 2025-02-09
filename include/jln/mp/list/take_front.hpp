// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/utility/conditional.hpp>
#include <jln/mp/utility/always.hpp>
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
    template<class... xs>
    using f = typename detail::take_front_impl<(sizeof...(xs) & 0) + N>
      ::template f<N, JLN_MP_TRACE_F(C)::template f, xs...>;
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
    using take_front = typename detail::_unpack<mp::take_front<N, C>, L>::type;

    template<class L, int_t n, class C = mp::listify>
    using take_front_c = typename detail::_unpack<mp::take_front_c<n, C>, L>::type;

    template<class L, class N, class C = mp::listify>
    using take_front_max = typename detail::_unpack<mp::take_front_max<N, C>, L>::type;

    template<class L, int_t n, class C = mp::listify>
    using take_front_max_c = typename detail::_unpack<mp::take_front_max_c<n, C>, L>::type;
  }


  /// \cond
  #if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_DEBUG
  template<unsigned N, template<class...> class C>
  struct take_front_c<N, cfe<C>>
  {
    template<class... xs>
    using f = typename detail::take_front_impl<(sizeof...(xs) & 0) + N>
      ::template f<N, C, xs...>;
  };
  #endif
  /// \endcond
}


/// \cond
namespace jln::mp::detail
{
  template<unsigned n>
  struct take_front_impl : take_front_impl<
      n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

  template<>
  struct take_front_impl<0>
  {
    template<unsigned size, template<class...> class C, class... xs>
    using f = C<>;
  };

#define JLN_MP_TAKE_IMPL(n, mp_xs, mp_rxs, mp_rep)            \
  template<>                                                  \
  struct take_front_impl<n>                                   \
  {                                                           \
    template<unsigned size, template<class...> class C,       \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)                  \
      class... xs>                                            \
    using f = C<mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>; \
  };

  JLN_MP_GEN_XS_1_TO_16(JLN_MP_TAKE_IMPL)

#undef JLN_MP_TAKE_IMPL

#define JLN_MP_TAKE_IMPL(n, mp_xs, mp_rxs, mp_rep)                      \
  template<>                                                            \
  struct take_front_impl<n>                                             \
  {                                                                     \
    template<unsigned size, template<class...> class C,                 \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)                            \
      class... xs>                                                      \
    using f = typename _join_select<2>::f<C,                            \
      list<mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,                \
      typename take_front_impl<size-n>::template f<size-n, list, xs...> \
    >::type;                                                            \
  };

  JLN_MP_GEN_XS_16_64_256(JLN_MP_TAKE_IMPL)

#undef JLN_MP_TAKE_IMPL
}
/// \endcond
