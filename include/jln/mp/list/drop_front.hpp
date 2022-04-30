#pragma once

#include <jln/mp/detail/enumerate.hpp>
#include <jln/mp/list/listify.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/unpack.hpp>

#include <cstddef>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned>
    struct drop_front_impl;
  }
  /// \endcond

  /// \ingroup list

  /// Removes \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N <= sizeof...(xs)`
  /// \treturn \sequence
  /// \see drop_front_max, drop_back, take_front, take_back, drop_while
#ifdef JLN_MP_DOXYGENATING
  template<unsigned N, class C = listify>
  struct drop_front_c
  {
    template<class... xs>
    using f;
  };
#else
  template<unsigned N, class C = listify>
  struct drop_front_c;
#endif

  /// Removes at most \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while
  template<unsigned N, class C = listify>
  struct drop_front_max_c
  {
    template<class... xs>
    using f = typename detail::drop_front_impl<
      detail::min(N, sizeof...(xs))
    >::template f<
      detail::min(N, sizeof...(xs)),
      JLN_MP_TRACE_F(C)::template f,
      xs...
    >;
  };

  template<class N, class C = listify>
  using drop_front = drop_front_c<N::value, C>;

  template<class N, class C = listify>
  using drop_front_max = drop_front_max_c<N::value, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using drop_front = unpack<L, mp::drop_front<N, C>>;

    template<class L, unsigned n, class C = mp::listify>
    using drop_front_c = unpack<L, mp::drop_front_c<n, C>>;

    template<class L, class N, class C = mp::listify>
    using drop_front_max = unpack<L, mp::drop_front_max<N, C>>;

    template<class L, unsigned n, class C = mp::listify>
    using drop_front_max_c = unpack<L, mp::drop_front_max_c<n, C>>;
  }

  /// \cond
  template<unsigned N, class C>
  struct drop_front_c
  {
    template<class, class, class, class, class, class,
             class, class, class, class, class... xs>
    using f = typename detail::drop_front_impl<
      (sizeof...(xs) & 0) + N - 10
    >::template f<N-10, JLN_MP_TRACE_F(C)::template f, xs...>;
  };

  template<class C>
  struct drop_front_c<0, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };

  template<class C>
  struct drop_front_max_c<0, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };

  template<>
  struct drop_front_c<0, listify>
  {
    template<class... xs>
    using f = list<xs...>;
  };

  template<>
  struct drop_front_max_c<0, listify>
  {
    template<class... xs>
    using f = list<xs...>;
  };

  #define JLN_MP_DROP_FRONT(n, mp_xs, mp_rxs, mp_dup)    \
    template<class C>                                    \
    struct drop_front_c<n, C>                            \
    {                                                    \
      template<mp_dup(class, JLN_MP_COMMA), class... xs> \
      using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);     \
    };

  JLN_MP_GEN_XS_1_TO_8_INCLUDED(JLN_MP_DROP_FRONT)
  JLN_MP_DROP_FRONT(9, x, x, JLN_MP_REPEAT_9)
  #undef JLN_MP_DROP_FRONT

  #if ! JLN_MP_ENABLE_DEBUG
  template<unsigned N, template<class...> class C>
  struct drop_front_c<N, lift<C>>
  {
    template<class, class, class, class, class, class,
             class, class, class, class, class... xs>
    using f = typename detail::drop_front_impl<
      (sizeof...(xs) & 0) + N-10
    >::template f<N-10, C, xs...>;
  };

  template<unsigned N, template<class...> class C>
  struct drop_front_max_c<N, lift<C>>
  {
    template<class... xs>
    using f = typename detail::drop_front_impl<
      detail::min(N, sizeof...(xs))
    >::template f<detail::min(N, sizeof...(xs)), C, xs...>;
  };

  template<template<class...> class C>
  struct drop_front_c<0, lift<C>> : lift<C>
  {};

  template<template<class...> class C>
  struct drop_front_max_c<0, lift<C>> : lift<C>
  {};

  #define JLN_MP_DROP_FRONT(n, mp_xs, mp_rxs, mp_dup)    \
    template<template<class...> class C>                 \
    struct drop_front_c<n, lift<C>>                      \
    {                                                    \
      template<mp_dup(class, JLN_MP_COMMA), class... xs> \
      using f = C<xs...>;                                \
    };

  JLN_MP_GEN_XS_1_TO_8_INCLUDED(JLN_MP_DROP_FRONT)
  JLN_MP_DROP_FRONT(9, x, x, JLN_MP_REPEAT_9)
  #undef JLN_MP_DROP_FRONT

  #endif
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template<unsigned n>
  struct drop_front_impl : drop_front_impl<
      n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

#define JLN_MP_DROP_IMPL(n, _, mp_rxs, mp_rep) \
  template<>                                   \
  struct drop_front_impl<n>                    \
  {                                            \
    template<unsigned size,                    \
      template<class...> class C,              \
      mp_rep(class JLN_MP_COMMA, JLN_MP_NIL)   \
      class... xs>                             \
    using f = C<xs...>;                        \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_MP_DROP_IMPL)

#undef JLN_MP_DROP_IMPL

#define JLN_MP_DROP_IMPL(n, _, mp_rxs, mp_rep) \
  template<>                                   \
  struct drop_front_impl<n>                    \
  {                                            \
    template<unsigned size,                    \
      template<class...> class C,              \
      mp_rep(class JLN_MP_COMMA, JLN_MP_NIL)   \
      class... xs>                             \
    using f = typename drop_front_impl<size-n> \
      ::template f<size-n, C, xs...>;          \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_DROP_IMPL)

#undef JLN_MP_DROP_IMPL
}
/// \endcond
