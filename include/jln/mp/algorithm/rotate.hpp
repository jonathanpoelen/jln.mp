#pragma once

#include "../config/enumerate.hpp"
#include "../list/list.hpp"
#include "../number/number.hpp"
#include "../functional/call.hpp"
#include "../utility/conditional.hpp"

namespace jln::mp
{
  namespace detail
  {
    template <unsigned n>
    struct _rotate;

    constexpr unsigned _rotate_size(int_ n, unsigned size)
    {
      return n >= size
        ? (size == 0 ? 0 : n % size)
        : (n < 0 ? (size && n % size ? size + n % size : 0) : n);
    }
  }

  template <class N, class C = listify>
  struct rotate
  {
    template<class... xs>
    // TODO detail::dcalli
    using f = typename conditional_c<(sizeof...(xs) < 1000000)>
      ::template f<
        detail::_rotate<detail::n_8_or_less_16_64_256(
          detail::_rotate_size(N::value, sizeof...(xs))
        )>,
        void>
      ::template f<
        detail::_rotate_size(N::value, sizeof...(xs)),
        C, xs...>;
  };

  template <int_ n, class C = listify>
  using rotate_c = rotate<number<n>, C>;

  namespace emp
  {
    template <class n, class... xs>
    using rotate = mp::call<mp::rotate<n>, xs...>;

    template <int_ n, class... xs>
    using rotate_c = mp::call<mp::rotate<number<n>>, xs...>;
  }
}


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
