#pragma once

#include "../list/drop.hpp"
#include "../utility/same_as.hpp"
#include "../number/operators.hpp"
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

  template<int_ x, class C = listify, class NC = C>
  using lower_bound_c = lower_bound<less_than_c<x>, C, NC>;

  template<int_ x, class C = listify, class NC = C>
  using upper_bound_c = lower_bound<greater_equal_than_c<x>, C, NC>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify, class NC = C>
    using lower_bound = eager<L, mp::lower_bound<Pred, C, NC>>;

    template<class L, int_ x, class C = mp::listify, class NC = C>
    using lower_bound_c = eager<L, mp::lower_bound_c<x, C, NC>>;

    template<class L, int_ x, class C = mp::listify, class NC = C>
    using upper_bound_c = eager<L, mp::upper_bound_c<x, C, NC>>;
  }
}


#include "cartesian.hpp"
#include "../config/enumerate.hpp"
#include "../list/pop_front.hpp"
#include "../list/front.hpp"
#include "../list/drop.hpp"

namespace jln::mp::detail
{
  template<int>
  struct _smp_lower_bound;

  template<class Bool, class = void>
  struct _smp_conditional
  {
    template<class C, class NC>
    using f = violation;
  };

  template<class Bool>
  struct _smp_conditional<Bool, decltype(void(bool(Bool::value)))>
  {
    template<class C, class NC>
    using f = typename conditional_c<bool(Bool::value)>::template f<C, NC>;
  };

#define JLN_MP_LOWER_BOUND_IMPL(prefix, Cond)              \
  template<>                                               \
  struct prefix##lower_bound<0>                            \
  {                                                        \
    template<unsigned n, class Pred, class C, class NC,    \
      class... xs>                                         \
    using f = typename NC::template f<>;                   \
  };                                                       \
                                                           \
  /* original size == 1 */                                 \
  template<>                                               \
  struct prefix##lower_bound<-1>                           \
  {                                                        \
    template<unsigned n, class Pred, class C, class NC,    \
      class x>                                             \
    using f = Cond(x)                                      \
      ::template f<_cartesian<NC, 0> /* for NC::f<> */, C> \
      ::template f<x>;                                     \
  };                                                       \
                                                           \
  template<>                                               \
  struct prefix##lower_bound<1>                            \
  {                                                        \
    template<unsigned n, class Pred, class C, class NC,    \
      class x, class... xs>                                \
    using f = Cond(x)                                      \
      ::template f<pop_front<C>, C>                        \
      ::template f<x, xs...>;                              \
  };

#define JLN_MP_LOWER_BOUND_PRED_CALL(x) \
  typename conditional_c<bool(Pred::template f<x>::value)>

#define JLN_MP_LOWER_BOUND_SMP_PRED_CALL(x) \
  typename _smp_conditional<typename Pred::template f<x>>

  JLN_MP_LOWER_BOUND_IMPL(_, JLN_MP_LOWER_BOUND_PRED_CALL)
  JLN_MP_LOWER_BOUND_IMPL(_smp_, JLN_MP_LOWER_BOUND_SMP_PRED_CALL)

#undef JLN_MP_LOWER_BOUND_IMPL

  template<unsigned> struct _lower_bound_drop;
  template<unsigned> struct _smp_lower_bound_drop;

#define JLN_MP_LOWER_BOUND_IMPL2(prefix, Cond, n, mp_xs) \
  template<>                                             \
  struct prefix##lower_bound_drop<n>                     \
  {                                                      \
    template<int count, class Pred, class C, class NC,   \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),            \
      class... xs>                                       \
    using f = typename detail::prefix##lower_bound<      \
      _lower_bound_select(count-n)                       \
    >::template f<count-n, Pred, C, NC, xs...>;          \
  };                                                     \
                                                         \
  template<>                                             \
  struct prefix##lower_bound<n>                          \
  {                                                      \
    template<int count, class Pred, class C, class NC,   \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),            \
      class... xs>                                       \
    using f = Cond(_##n)::template f<                    \
      prefix##lower_bound_drop<n>,                       \
      prefix##lower_bound<n/2>                           \
    >::template f<count, Pred, C, NC,                    \
      mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),       \
      xs...                                              \
    >;                                                   \
  };

#define JLN_MP_LOWER_BOUND_IMPL(n, mp_xs, mp_rxs, mp_rep)             \
  JLN_MP_LOWER_BOUND_IMPL2(_, JLN_MP_LOWER_BOUND_PRED_CALL, n, mp_xs) \
  JLN_MP_LOWER_BOUND_IMPL2(_smp_, JLN_MP_LOWER_BOUND_SMP_PRED_CALL, n, mp_xs)

  JLN_MP_GEN_XS_2_4_8_16_32_64_128_256(JLN_MP_LOWER_BOUND_IMPL)

#undef JLN_MP_LOWER_BOUND_IMPL
#undef JLN_MP_LOWER_BOUND_PRED_CALL
#undef JLN_MP_LOWER_BOUND_SMP_PRED_CALL
}
