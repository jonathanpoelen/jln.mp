// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/sequence.hpp>
#include <jln/mp/list/listify.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/utility/conditional.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned n>
    struct rotate_impl;

    constexpr unsigned rotate_size(int_t n, unsigned size);
  }
  /// \endcond

  /// \ingroup algorithm

  /// Rotates the elements of a \sequence around a pivot.
  /// \tparam N  a negative value start to end of sequence. The final offset is a modulo of `sizeof...(xs)`.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///     len = sizeof...(xs)
  ///     n = len ? (N < 0 ? len + N % len : N) % size : 0
  ///
  ///     C::f<...xs[n:], ...xs[:n]>
  ///   \endcode
  /// \treturn \sequence
  template<int_t N, class C = listify>
  struct rotate_c
  {
    template<class... xs>
    using f = typename detail::rotate_impl<
      detail::rotate_size(N, sizeof...(xs))
    >
    ::template f<
      detail::rotate_size(N, sizeof...(xs)),
      JLN_MP_TRACE_F(C)::template f, xs...
    >;
  };

  template<class N, class C = listify>
  using rotate = rotate_c<N::value, C>;

  namespace emp
  {
    template<class L, class n, class C = mp::listify>
    using rotate = typename detail::_unpack<mp::rotate<n, C>, L>::type;

    template<class L, int_t n, class C = mp::listify>
    using rotate_c = typename detail::_unpack<mp::rotate_c<n, C>, L>::type;
  }
}


#include <jln/mp/list/front.hpp>

/// \cond
namespace jln::mp
{
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
  template<int_t N, template<class...> class C>
  struct rotate_c<N, lift<C>>
  {
    template<class... xs>
    using f = typename detail::rotate_impl<
      detail::rotate_size(N, sizeof...(xs))
    >
    ::template f<
      detail::rotate_size(N, sizeof...(xs)),
      C, xs...
    >;
  };
#endif

  template<int_t N1, int_t N2, class C>
  struct rotate_c<N1, rotate_c<N2, C>>
    : rotate_c<N1 + N2, C>
  {};

#if JLN_MP_HAS_BUILTIN(__type_pack_element)
  // back<C>
  template<int_t N, class C>
  struct rotate_c<N, front<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      __type_pack_element<detail::rotate_size(N, sizeof...(xs)), xs...>
    );
  };

  // back<>
  template<int_t N>
  struct rotate_c<N, front<>>
  {
    template<class... xs>
    using f = __type_pack_element<detail::rotate_size(N, sizeof...(xs)), xs...>;
  };
#endif
}

namespace jln::mp::detail
{
  constexpr unsigned rotate_size(int_t n, unsigned size)
  {
    return size ? static_cast<unsigned>(n < 0 ? size + n % size : n) % size : 0;
  }

  template<unsigned n>
  struct rotate_impl : rotate_impl<
      n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

#define JLN_MP_ROTATE_IMPL(n, mp_xs, mp_rxs, _)           \
  template<>                                              \
  struct rotate_impl<n>                                   \
  {                                                       \
    template<unsigned size, template<class...> class C,   \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)              \
      class... xs>                                        \
    using f = C<                                          \
      xs... mp_xs(JLN_MP_COMMA, JLN_MP_NIL, JLN_MP_NIL)>; \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_MP_ROTATE_IMPL)

#undef JLN_MP_ROTATE_IMPL

#define JLN_MP_ROTATE_IMPL(n, mp_xs, mp_rxs, _)           \
  template<>                                              \
  struct rotate_impl<n>                                   \
  {                                                       \
    template<unsigned size, template<class...> class C,   \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)              \
      class... xs>                                        \
    using f = typename rotate_impl<size-n>                \
      ::template f<size-n, C,                             \
        xs... mp_xs(JLN_MP_COMMA, JLN_MP_NIL, JLN_MP_NIL) \
      >;                                                  \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_ROTATE_IMPL)

#undef JLN_MP_ROTATE_IMPL
} // namespace jln::mp
/// \endcond
