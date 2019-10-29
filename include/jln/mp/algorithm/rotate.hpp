#pragma once

#include "../number/number.hpp"
#include "../functional/call.hpp"
#include "../list/list.hpp"

namespace jln::mp
{
  namespace detail
  {
    template <unsigned n>
    struct _rotate;

    // TODO n_8_or_less_16_64_256
    constexpr unsigned _rotate_step(unsigned n)
    {
      return
        n <= 8 ? n
      : n < 16 ? 8
      : n < 64 ? 16
      : n < 256 ? 64
      : 256
      ;
    }

    // TODO compatibility with negative n ?
    constexpr unsigned _rotate_size(unsigned n, unsigned size) {
      return n >= size ? (size == 0 ? 0 : n % size) : n;
    }
  }

  template <class n, class C = listify>
  struct rotate
  {
    template<class... xs>
    using f = typename detail::_rotate<
      detail::_rotate_step(
        detail::_rotate_size(n::value, sizeof...(xs)))
    >::template f<
      detail::_rotate_size(n::value, sizeof...(xs)),
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

#include "../config/enumerate.hpp"

namespace jln::mp::detail
{
  template <>
  struct _rotate<0>
  {
    template<unsigned size, class continuation, class... xs>
    using f = typename continuation::template f<xs...>;
  };

#define JLN_MP_ROTATE_IMPL(n, mp_xs, _)          \
  template<>                                     \
  struct _rotate<n>                              \
  {                                              \
    template<unsigned size, class continuation,  \
      mp_xs(class, JLN_MP_NIL), class... xs>     \
    using f = typename continuation::template f< \
      xs..., mp_xs(JLN_MP_NIL, JLN_MP_NIL)>;     \
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_ROTATE_IMPL)

#undef JLN_MP_ROTATE_IMPL

#define JLN_MP_ROTATE_IMPL(n, mp_xs, _)                            \
  template<>                                                       \
  struct _rotate<n>                                                \
  {                                                                \
    template<unsigned size, class continuation,                    \
      mp_xs(class, JLN_MP_NIL), class... xs>                       \
    using f = typename _rotate<_rotate_step(size-n)>::template f<  \
      size-n, continuation, xs..., mp_xs(JLN_MP_NIL, JLN_MP_NIL)>; \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_ROTATE_IMPL)

#undef JLN_MP_ROTATE_IMPL
} // namespace jln::mp
