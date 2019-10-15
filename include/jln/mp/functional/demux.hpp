#pragma once

#include "../functional/when.hpp"


namespace jln::mp
{
  namespace detail
  {
    template <unsigned n>
    struct _rotate;

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

    constexpr unsigned _rotate_size(unsigned n, unsigned size) {
      return n >= size ? (size == 0 ? 0 : n % size) : n;
    }
  }

  template <class n, class continuation = listify>
  struct rotate
  {
    template<class... xs>
    using f = typename detail::_rotate<
      detail::_rotate_step(
        detail::_rotate_size(n::value, sizeof...(xs)))
    >::template f<detail::_rotate_size(n::value, sizeof...(xs)),
      continuation, xs...>;
  };

  // TODO DOXY template<class... functions, class continuation>
  template <class... xs>
  struct demux : rotate<number<sizeof...(xs)-1>, cfe<detail::_demux>>::template f<xs...>
  {};

  template <class F, class C>
  struct demux<F, C>
  {
    template<class... xs>
    using f = typename C::template f<mp::call<F, xs...>>;
  };

  template <class F0, class F1, class C>
  struct demux<F0, F1, C>
  {
    template<class... xs>
    using f = typename C::template f<
      mp::call<F0, xs...>,
      mp::call<F1, xs...>
    >;
  };
}

namespace jln::mp::detail
{
  template <>
  struct _rotate<0>
  {
    template<unsigned size, class continuation, class... xs>
    using f = typename continuation::template f<xs...>;
  };

#define JLN_MP_ROTATE_IMPL(n, mp_xs)             \
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

#define JLN_MP_ROTATE_IMPL(n, mp_xs)                               \
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
