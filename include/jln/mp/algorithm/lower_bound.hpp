#pragma once

#include "../list/drop.hpp"
#include "../utility/same_as.hpp"
#include "../functional/identity.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<int>
    struct _lower_bound;

    constexpr int _lower_bound_select(unsigned n)
    {
      return
        n < 2 ? -n
      : n < 4 ? 2
      : n < 8 ? 4
      : n < 16 ? 8
      : n < 32 ? 16
      : n < 64 ? 32
      : n < 128 ? 64
      : n < 256 ? 128
      : 256
      ;
    }
  }

  template<class Pred, class C = listify, class NC = C>
  struct lower_bound
  {
    template<class... xs>
    using f = typename detail::_lower_bound<
      detail::_lower_bound_select(sizeof...(xs))
    >::template f<sizeof...(xs), Pred, C, NC, xs...>;
  };

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify, class NC = C>
    using lower_bound = eager<L, mp::lower_bound<Pred, C, NC>>;
  }
}


#include "cartesian.hpp"
#include "../config/enumerate.hpp"
#include "../list/pop_front.hpp"
#include "../list/front.hpp"
#include "../list/drop.hpp"

namespace jln::mp::detail
{
  template<>
  struct _lower_bound<0>
  {
    template<unsigned n, class Pred, class C, class NC, class... xs>
    using f = typename NC::template f<>;
  };

  // original size == 1
  template<>
  struct _lower_bound<-1>
  {
    template<unsigned n, class Pred, class C, class NC, class x>
    using f = typename conditional_c<bool(Pred::template f<x>::value)>
      ::template f<_cartesian<NC, 0> /* for NC::f<> */, C>
      ::template f<x>;
  };

  template<>
  struct _lower_bound<1>
  {
    template<unsigned n, class Pred, class C, class NC, class x, class... xs>
    using f = typename conditional_c<bool(Pred::template f<x>::value)>
      ::template f<pop_front<C>, C>
      ::template f<x, xs...>;
  };

  template<unsigned>
  struct _lower_bound_drop;

#define JLN_MP_LOWER_BOUND_IMPL(n, mp_xs, mp_rxs, mp_rep)   \
  template<>                                                \
  struct _lower_bound_drop<n>                               \
  {                                                         \
    template<int count, class Pred, class C, class NC,      \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),               \
      class... xs>                                          \
    using f = typename detail::_lower_bound<                \
      _lower_bound_select(count-n)                          \
    >::template f<count-n, Pred, C, NC, xs...>;             \
  };                                                        \
                                                            \
  template<>                                                \
  struct _lower_bound<n>                                    \
  {                                                         \
    template<int count, class Pred, class C, class NC,      \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),               \
      class... xs>                                          \
    using f = typename conditional_c<bool(                  \
      Pred::template f<_##n>::value                         \
    )>::template f<_lower_bound_drop<n>, _lower_bound<n/2>> \
      ::template f<count, Pred, C, NC,                      \
        mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),        \
        xs...                                               \
      >;                                                    \
  };

  JLN_MP_GEN_XS_2_4_8_16_32_64_128_256(JLN_MP_LOWER_BOUND_IMPL)

#undef JLN_MP_LOWER_BOUND_IMPL
}
