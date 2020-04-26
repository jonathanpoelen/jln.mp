#pragma once

#include "../config/enumerate.hpp"
#include "../list/list.hpp"
#include "../number/number.hpp"
#include "../utility/unpack.hpp"
#include "../utility/conditional.hpp"

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template <unsigned n>
    struct _rotate;

    constexpr unsigned _rotate_size(int_ n, unsigned size)
    {
      return n >= size
        ? (size ? n % size : 0)
        : (n < 0 ? (size && n % size ? size + n % size : 0) : n);
    }
  }
  /// \endcond

  /// \ingroup algorithm

  /// Rotates the elements of a \sequence around a pivot.
  /// \tparam N  a negative value start to end of sequence. The final offset is a modulo of `sizeof...(xs)`.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///     n = 0
  ///     len = sizeof...(xs)
  ///     if (len) {
  ///       n = N::value
  ///       if (n < 0) n = len + (n % len)
  ///       n = n % len
  ///     }
  ///     C::f<...xs[n:], ...xs[:n]>
  ///   \endcode
  /// \treturn \sequence
  template <class N, class C = listify>
  struct rotate
  {
    template<class... xs>
    using f = typename detail::_rotate<detail::n_8_or_less_16_64_256(
      detail::_rotate_size(N::value, sizeof...(xs))
    )>
    ::template f<
      detail::_rotate_size(N::value, sizeof...(xs)),
      C, xs...
    >;
  };

  template <int_ n, class C = listify>
  using rotate_c = rotate<number<n>, C>;

  namespace emp
  {
    template <class L, class n, class C = mp::listify>
    using rotate = unpack<L, mp::rotate<n, C>>;

    template <class L, int_ n, class C = mp::listify>
    using rotate_c = unpack<L, mp::rotate<number<n>, C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
#define JLN_MP_ROTATE_IMPL(n, mp_xs, mp_rxs, _)           \
  template<>                                              \
  struct _rotate<n>                                       \
  {                                                       \
    template<unsigned size, class C,                      \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)              \
      class... xs>                                        \
    using f = typename C::template f<                     \
      xs... mp_xs(JLN_MP_COMMA, JLN_MP_NIL, JLN_MP_NIL)>; \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_MP_ROTATE_IMPL)

#undef JLN_MP_ROTATE_IMPL

#define JLN_MP_ROTATE_IMPL(n, mp_xs, mp_rxs, mp_rep) \
  JLN_MP_ROTATE_IMPL2(n, mp_xs, mp_rep, mp_rxs,      \
    n_8_or_less_16_64_256)

#define JLN_MP_ROTATE_IMPL2(n, mp_xs, mp_rxs, _, next_int) \
  template<>                                               \
  struct _rotate<n>                                        \
  {                                                        \
    template<unsigned size, class C,                       \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)               \
      class... xs>                                         \
    using f = typename _rotate<next_int (size-n)>          \
      ::template f<size-n, C,                              \
        xs... mp_xs(JLN_MP_COMMA, JLN_MP_NIL, JLN_MP_NIL)  \
      >;                                                   \
  };

  JLN_MP_GEN_XS_8_args(JLN_MP_ROTATE_IMPL2, JLN_MP_NIL)
  JLN_MP_GEN_XS_16_64_256(JLN_MP_ROTATE_IMPL)

#undef JLN_MP_ROTATE_IMPL2
#undef JLN_MP_ROTATE_IMPL
} // namespace jln::mp
/// \endcond
