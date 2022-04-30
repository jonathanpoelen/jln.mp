#pragma once

#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/list/drop_front.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Extracts \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N <= sizeof...(xs)`
  /// \treturn \sequence
  /// \see take_front_max, take_back, drop_front, drop_back, take_while
  template<unsigned N, class C = listify>
  struct take_front_c
  {
    template<class... xs>
    using f = typename detail::rotate_impl<(sizeof...(xs) & 0) + N>
      ::template f<N, drop_front_c<sizeof...(xs) - N, C>, xs...>;
  };

  /// Extracts at most \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  /// \see take_front, take_back, take_while
  template<unsigned N, class C = listify>
  struct take_front_max_c
  {
    template<class... xs>
    using f = typename detail::rotate_impl<sizeof...(xs) < N ? 0 : N>
      ::template f<
        N,
        drop_front_max_c<sizeof...(xs) < N ? 0 : sizeof...(xs) - N, C>,
        xs...
      >;
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
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS_0(xs, C);
  };

  template<class C>
  struct take_front_max_c<0, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS_0(xs, C);
  };

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
  JLN_MP_TAKE_FRONT(9, JLN_MP_XS_9, x, x)
  #undef JLN_MP_TAKE_FRONT
  /// \endcond
}

