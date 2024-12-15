// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/sequence.hpp>
#include <jln/mp/list/listify.hpp>
#include <jln/mp/list/front.hpp>
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
  template<unsigned N, class C = listify>
  struct drop_front_c
  {
    template<class... xs>
    using f = typename detail::drop_front_impl<(sizeof...(xs) & 0) + N>
      ::template f<N, JLN_MP_TRACE_F(C)::template f, xs...>;
  };

  /// Removes at most \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while
  template<unsigned N, class C = listify>
  struct drop_front_max_c
  {
    template<class... xs>
    using f = typename detail::drop_front_impl<
      sizeof...(xs) < N ? sizeof...(xs) : N
    >::template f<
      sizeof...(xs) < N ? sizeof...(xs) : N,
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
    using drop_front = typename detail::_unpack<mp::drop_front<N, C>, L>::type;

    template<class L, unsigned n, class C = mp::listify>
    using drop_front_c = typename detail::_unpack<mp::drop_front_c<n, C>, L>::type;

    template<class L, class N, class C = mp::listify>
    using drop_front_max = typename detail::_unpack<mp::drop_front_max<N, C>, L>::type;

    template<class L, unsigned n, class C = mp::listify>
    using drop_front_max_c = typename detail::_unpack<mp::drop_front_max_c<n, C>, L>::type;
  }

  /// \cond
  template<class C>
  struct drop_front_c<0, C>
    : detail::call_trace_xs<C>
  {};

  template<class C>
  struct drop_front_max_c<0, C>
    : detail::call_trace_xs<C>
  {};

  template<>
  struct drop_front_c<0, listify> : listify
  {};

  template<>
  struct drop_front_max_c<0, listify> : listify
  {};

#if JLN_MP_ENABLE_TYPE_PACK_ELEMENT
  template<unsigned N, class C>
  struct drop_front_c<N, front<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, __type_pack_element<N, xs...>);
  };

  template<class C>
  struct drop_front_c<0, front<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, __type_pack_element<0, xs...>);
  };


  template<unsigned N>
  struct drop_front_c<N, front<identity>>
  {
    template<class... xs>
    using f = __type_pack_element<N, xs...>;
  };

  template<>
  struct drop_front_c<0, front<identity>>
  {
    template<class... xs>
    using f = __type_pack_element<0, xs...>;
  };


  template<unsigned N, class C>
  struct drop_front_max_c<N, front<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      __type_pack_element<sizeof...(xs) < N ? sizeof...(xs) : N, xs...>
    );
  };

  template<class C>
  struct drop_front_max_c<0, front<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      __type_pack_element<0, xs...>
    );
  };


  template<unsigned N>
  struct drop_front_max_c<N, front<identity>>
  {
    template<class... xs>
    using f = __type_pack_element<sizeof...(xs) < N ? sizeof...(xs) : N, xs...>;
  };

  template<>
  struct drop_front_max_c<0, front<identity>>
  {
    template<class... xs>
    using f = __type_pack_element<0, xs...>;
  };
#endif

#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
  template<unsigned N, template<class...> class C>
  struct drop_front_c<N, lift<C>>
  {
    template<class... xs>
    using f = typename detail::drop_front_impl<(sizeof...(xs) & 0) + N>
      ::template f<N, C, xs...>;
  };

  template<unsigned N, template<class...> class C>
  struct drop_front_max_c<N, lift<C>>
  {
    template<class... xs>
    using f = typename detail::drop_front_impl<
      sizeof...(xs) < N ? sizeof...(xs) : N
    >::template f<
      sizeof...(xs) < N ? sizeof...(xs) : N,
      C, xs...
    >;
  };
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
