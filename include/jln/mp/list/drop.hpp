#pragma once

#include "../config/enumerate.hpp"
#include "../list/list.hpp"
#include "../number/number.hpp"
#include "../utility/eager.hpp"
#include "../utility/conditional.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<unsigned>
    struct _drop;

    template<int_ i, unsigned n>
    using validate_index = number<(0 * std::size_t{int_(n) - i}) + i>;
  }

  template<class N, class C = listify>
  struct drop
  {
    template<class... xs>
    // TODO detail::dcalli
    using f = typename detail::_drop<
      detail::n_8_or_less_16_64_256(
        detail::validate_index<N::value, sizeof...(xs)>::value
      )
    >::template f<N::value, C, xs...>;
  };

  template<int_ n, class C = listify>
  using drop_c = drop<number<n>, C>;

  template<class C>
  struct drop<number<0>, C>
  {
    template<class... xs>
    using f = call<C, xs...>;
  };

  template<class C>
  struct drop<number<1>, C>
  {
    template<class x0, class... xs>
    using f = call<C, xs...>;
  };

  template<class C>
  struct drop<number<2>, C>
  {
    template<class x0, class x1, class... xs>
    using f = call<C, xs...>;
  };

  // TODO more drop

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using drop = eager<L, mp::drop<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using drop_c = eager<L, mp::drop<number<n>, C>>;
  }
}

namespace jln::mp::detail
{
#define JLN_MP_DROP_IMPL(n, _, mp_rxs, mp_rep) \
  template<>                                   \
  struct _drop<n>                              \
  {                                            \
    template<unsigned size, class C,           \
      mp_rep(class JLN_MP_COMMA, JLN_MP_NIL)   \
      class... xs>                             \
    using f = typename C::template f<xs...>;   \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_MP_DROP_IMPL)

#undef JLN_MP_DROP_IMPL

#define JLN_MP_DROP_IMPL(n, mp_xs, mp_rxs, mp_rep) \
  JLN_MP_DROP_IMPL2(n, mp_xs, mp_rxs, mp_rep,      \
    n_8_or_less_16_64_256)

#define JLN_MP_DROP_IMPL2(n, _, mp_rxs, mp_rep, next_int) \
  template<>                                              \
  struct _drop<n>                                         \
  {                                                       \
    template<unsigned size, class C,                      \
      mp_rep(class JLN_MP_COMMA, JLN_MP_NIL)              \
      class... xs>                                        \
    using f = typename _drop<next_int (size-n)>           \
      ::template f<(size-n), C, xs...>;                   \
  };

  JLN_MP_GEN_XS_8_args(JLN_MP_DROP_IMPL2, JLN_MP_NIL)
  JLN_MP_GEN_XS_16_64_256(JLN_MP_DROP_IMPL)

#undef JLN_MP_DROP_IMPL2
#undef JLN_MP_DROP_IMPL
}
