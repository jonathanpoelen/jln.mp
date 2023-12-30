// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/operators.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct _lower_bound;

    constexpr int _lower_bound_select(unsigned n);

    template<class>
    struct optimize_cmp;
  }
  /// \endcond

  /// \ingroup search

  /// Finds first element that is not less than (i.e. greater or equal to) \c x.
  /// Calls \c TC with all the elements since the one found at the end.
  /// If no element is found, \c FC is used.
  /// \pre \c is_sorted<Cmp>::f<xs...>
  /// \treturn \sequence
  template<class x, class Cmp = less<>, class TC = listify, class FC = TC>
  struct lower_bound
  {
    template<class... xs>
    using f = typename detail::_lower_bound<
      detail::_lower_bound_select(sizeof...(xs))
    >::template f<
      sizeof...(xs),
      push_back<x, JLN_MP_TRACE_F(typename detail::optimize_cmp<Cmp>::type)>,
      TC, FC, xs...>;
  };

  template<int_ x, class Cmp = less<>, class TC = listify, class FC = TC>
  using lower_bound_c = lower_bound<number<x>, Cmp, TC, FC>;

  template<class x, class TC = listify, class FC = TC>
  using lower_bound_than = lower_bound<x, less<>, TC, FC>;

  template<int_ x, class TC = listify, class FC = TC>
  using lower_bound_than_c = lower_bound<number<x>, less<>, TC, FC>;

  namespace emp
  {
    template<class L, class x, class Cmp = mp::less<>, class TC = mp::listify, class FC = TC>
    using lower_bound = unpack<L, mp::lower_bound<x, Cmp, TC, FC>>;

    template<class L, int_ x, class Cmp = mp::less<>, class TC = mp::listify, class FC = TC>
    using lower_bound_c = unpack<L, mp::lower_bound<mp::number<x>, Cmp, TC, FC>>;

    template<class L, class x, class TC = mp::listify, class FC = TC>
    using lower_bound_than = unpack<L, mp::lower_bound<x, mp::less<>, TC, FC>>;

    template<class L, int_ x, class TC = mp::listify, class FC = TC>
    using lower_bound_than_c = unpack<L, mp::lower_bound<mp::number<x>, mp::less<>, TC, FC>>;
  }
}


#include <jln/mp/detail/sequence.hpp>
#include <jln/mp/list/pop_front.hpp>
#include <jln/mp/list/clear.hpp>
#include <jln/mp/functional/tee.hpp>
#include <jln/mp/functional/flip.hpp>
#include <jln/mp/functional/try.hpp> // na

/// \cond
namespace jln::mp::detail
{
  template<class Cmp>
  struct optimize_cmp
  {
    using type = Cmp;
  };

  template<class Cmp, class C>
  struct optimize_cmp<flip<tee<flip<Cmp>, C>>>
  : optimize_cmp<tee<Cmp, C>>
  {};

  template<class C>
  struct optimize_cmp<tee<less<>, C>>
  {
    using type = less<C>;
  };

  template<int>
  struct _smp_lower_bound;

  template<class Bool>
  struct _smp_conditional;

  template<>
  struct _smp_conditional<na>
  {
    template<class C, class FC>
    using f = violation;
  };

  template<>
  struct _smp_conditional<true_>
  {
    template<class C, class FC>
    using f = C;
  };

  template<>
  struct _smp_conditional<false_>
  {
    template<class C, class FC>
    using f = FC;
  };

  struct _lower_bound_violation2
  {
    template<unsigned, class...>
    using f = na;
  };

  template<class Bool>
  struct _smp_conditional2;

  template<>
  struct _smp_conditional2<na>
  {
    template<class C, class FC>
    using f = _lower_bound_violation2;
  };

  template<>
  struct _smp_conditional2<true_>
  {
    template<class C, class FC>
    using f = C;
  };

  template<>
  struct _smp_conditional2<false_>
  {
    template<class C, class FC>
    using f = FC;
  };

  constexpr int _lower_bound_select(unsigned n)
  {
    return
      n < 2 ? -int(n)
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

#define JLN_MP_LOWER_BOUND_IMPL(prefix, Cond)           \
  template<>                                            \
  struct prefix##lower_bound<0>                         \
  {                                                     \
    template<unsigned n, class Cmp, class C, class FC, \
      class... xs>                                      \
    using f = JLN_MP_CALL_TRACE_0_ARG(FC);              \
  };                                                    \
                                                        \
  /* original size == 1 */                              \
  template<>                                            \
  struct prefix##lower_bound<-1>                        \
  {                                                     \
    template<unsigned n, class Cmp, class C, class FC, \
      class x>                                          \
    using f = JLN_MP_CALL_TRACE_T(JLN_MP_IDENT(Cond(x)  \
      ::template f<clear<FC>, C>),                      \
      x);                                               \
  };                                                    \
                                                        \
  template<>                                            \
  struct prefix##lower_bound<1>                         \
  {                                                     \
    template<unsigned n, class Cmp, class C, class FC, \
      class x, class... xs>                             \
    using f = JLN_MP_CALL_TRACE_T(JLN_MP_IDENT(Cond(x)  \
      ::template f<pop_front<C>, C>),                   \
      x, xs...);                                        \
  };

#define JLN_MP_LOWER_BOUND_PRED_CALL(x) \
  conditional_c<bool(Cmp::template f<x>::value)>

#define JLN_MP_LOWER_BOUND_SMP_PRED_CALL(x) \
  _smp_conditional<typename Cmp::template f<x>>

  JLN_MP_LOWER_BOUND_IMPL(_, JLN_MP_LOWER_BOUND_PRED_CALL)
  JLN_MP_LOWER_BOUND_IMPL(_smp_, JLN_MP_LOWER_BOUND_SMP_PRED_CALL)

#undef JLN_MP_LOWER_BOUND_IMPL

  template<unsigned> struct _lower_bound_drop_front;
  template<unsigned> struct _smp_lower_bound_drop_front;

#define JLN_MP_LOWER_BOUND_IMPL2(prefix, Cond, n, mp_xs) \
  template<>                                             \
  struct prefix##lower_bound_drop_front<n>               \
  {                                                      \
    template<int count, class Cmp, class C, class FC,   \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),            \
      class... xs>                                       \
    using f = typename detail::prefix##lower_bound<      \
      _lower_bound_select(count-n)                       \
    >::template f<count-n, Cmp, C, FC, xs...>;          \
  };                                                     \
                                                         \
  template<>                                             \
  struct prefix##lower_bound<n>                          \
  {                                                      \
    template<int count, class Cmp, class C, class FC,   \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),            \
      class... xs>                                       \
    using f = typename Cond(_##n)::template f<           \
      prefix##lower_bound_drop_front<n>,                 \
      prefix##lower_bound<n/2>                           \
    >::template f<count, Cmp, C, FC,                    \
      mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),       \
      xs...                                              \
    >;                                                   \
  };

#undef JLN_MP_LOWER_BOUND_SMP_PRED_CALL
#define JLN_MP_LOWER_BOUND_SMP_PRED_CALL(x) \
  _smp_conditional2<typename Cmp::template f<x>>

#define JLN_MP_LOWER_BOUND_IMPL(n, mp_xs, mp_rxs, mp_rep)             \
  JLN_MP_LOWER_BOUND_IMPL2(_, JLN_MP_LOWER_BOUND_PRED_CALL, n, mp_xs) \
  JLN_MP_LOWER_BOUND_IMPL2(_smp_, JLN_MP_LOWER_BOUND_SMP_PRED_CALL, n, mp_xs)

  JLN_MP_GEN_XS_2_4_8_16_32_64_128_256(JLN_MP_LOWER_BOUND_IMPL)

#undef JLN_MP_LOWER_BOUND_IMPL
#undef JLN_MP_LOWER_BOUND_PRED_CALL
#undef JLN_MP_LOWER_BOUND_SMP_PRED_CALL
}
/// \endcond
