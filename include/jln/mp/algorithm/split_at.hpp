// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned n>
    struct split_at_impl;

    template<class C, class C1, class C2, class L>
    struct split_at_with_impl;
  }
  /// \endcond


  /// \ingroup group

  /// Splits a sequence at an arbitrary position.
  /// \pre `i >= 0 && i <= sizeof...(xs)`
  /// \treturn \sequence of two \values
  template<unsigned i, class SubC1 = listify, class SubC2 = SubC1, class C = listify>
  struct split_at2_with_c
  {
    template<class... xs>
    using f = typename detail::split_at_with_impl<C, SubC1, SubC2,
      typename JLN_MP_CALLER_TRACE_XS(xs, detail::split_at_impl<i>)
      ::template f<i, list<>, xs...>
    >::type;
  };

  template<class i, class SubC1 = listify, class SubC2 = SubC1, class C = listify>
  using split_at2_with = split_at2_with_c<i::value, SubC1, SubC2, C>;

  template<unsigned i, class F = listify, class C = listify>
  using split_at_with_c = split_at2_with_c<i, F, F, C>;

  template<class i, class F = listify, class C = listify>
  using split_at_with = split_at2_with_c<i::value, F, F, C>;

  /// Splits a sequence at an arbitrary position.
  /// \pre `i >= 0 && i <= sizeof...(xs)`
  /// \treturn \sequence of two \lists
  template<unsigned i, class C = listify>
  using split_at_c = split_at2_with_c<i, listify, listify, C>;

  template<class i, class C = listify>
  using split_at = split_at2_with_c<i::value, listify, listify, C>;

  namespace emp
  {
    template<class L, class i, class SubC1 = mp::listify, class SubC2 = mp::listify,
             class C = mp::listify>
    using split_at2_with = unpack<L, mp::split_at2_with_c<i::value, SubC1, SubC2, C>>;

    template<class L, unsigned i, class SubC1 = mp::listify, class SubC2 = mp::listify,
             class C = mp::listify>
    using split_at2_with_c = unpack<L, mp::split_at2_with_c<i, SubC1, SubC2, C>>;

    template<class L, class i, class F = mp::listify, class C = mp::listify>
    using split_at_with = unpack<L, mp::split_at2_with_c<i::value, F, F, C>>;

    template<class L, unsigned i, class F = mp::listify, class C = mp::listify>
    using split_at_with_c = unpack<L, mp::split_at2_with_c<i, F, F, C>>;

    template<class L, class i, class C = mp::listify>
    using split_at = unpack<L, mp::split_at2_with_c<i::value, listify, listify, C>>;

    template<class L, unsigned i, class C = mp::listify>
    using split_at_c = unpack<L, mp::split_at2_with_c<i, listify, listify, C>>;
  }
}

/// \cond
namespace jln::mp
{
  template<unsigned i>
  struct split_at2_with_c<i, listify, listify, listify>
  {
    template<class... xs>
    using f = typename JLN_MP_CALLER_TRACE_XS(xs, detail::split_at_impl<i>)
      ::template f<i, list<>, xs...>;
  };
}

#include <jln/mp/list/join.hpp>

namespace jln::mp::detail
{
  template<unsigned n>
  struct split_at_impl : split_at_impl<
      n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

  template<>
  struct split_at_impl<0>
  {
    template<unsigned size, class L, class... xs>
    using f = list<L, list<xs...>>;
  };

#define JLN_MP_SPLIT_AT_IMPL(n, mp_xs, mp_rxs, mp_rep)  \
  template<>                                            \
  struct split_at_impl<n>                               \
  {                                                     \
    template<unsigned size,                             \
      class L,                                          \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)            \
      class... xs>                                      \
    using f = list<typename _join_select<2>::f<list, L, \
      list<mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)> \
    >::type, list<xs...>>;                              \
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_SPLIT_AT_IMPL)

#undef JLN_MP_SPLIT_AT_IMPL

#define JLN_MP_SPLIT_AT_IMPL(n, mp_xs, mp_rxs, mp_rep)      \
  template<>                                                \
  struct split_at_impl<n>                                   \
  {                                                         \
    template<unsigned size,                                 \
      class L,                                              \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)                \
      class... xs>                                          \
    using f = typename split_at_impl<size-n>                \
      ::template f<size-n,                                  \
        typename _join_select<2>::f<list, L,                \
          list<mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)> \
        >::type,                                            \
        xs...                                               \
      >;                                                    \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_SPLIT_AT_IMPL)

#undef JLN_MP_SPLIT_AT_IMPL

  template<class C, class C1, class C2, class... xs, class... ys>
  struct split_at_with_impl<C, C1, C2, list<list<xs...>, list<ys...>>>
  {
    using type = typename C::template f<
      typename C1::template f<xs...>,
      typename C2::template f<ys...>
    >;
  };
}
/// \endcond
