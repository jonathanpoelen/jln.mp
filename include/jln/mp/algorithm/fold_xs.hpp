// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/if.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/list/push_front.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct fold_xs_impl;

    constexpr int_t partial_fold_xs_size(int_t i, int_t size);

    template<template<class...> class F, int_t n, class... xs>
    using partial_fold_xs_select = typename detail::fold_xs_impl<n-1>
      ::template f<F, n-1, xs...>;
  }
  /// \endcond

  /// \ingroup reduce

  /// As \c fold_xs, but stop at position \c OffsetEnd.
  template<int_t OffsetEnd, class F, class C = identity>
  struct partial_fold_xs_c
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      detail::partial_fold_xs_select<
        JLN_MP_TRACE_F(F)::template f,
        detail::partial_fold_xs_size(OffsetEnd, sizeof...(xs)),
        xs...
      >
    );
  };

  template<class OffsetEnd, class F, class C = identity>
  using partial_fold_xs = partial_fold_xs_c<OffsetEnd::value, F, C>;

  /// Folds left over a list using a mulary predicate.
  /// The first element in the input pack as the state,
  /// use \c push_front<> to add state if needed.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<... F::f<xs[0], xs[1], ..., xs[n-1]>, xs[2], ..., xs[n-1]>, ..., xs[n-1]>, ...>
  ///   \endcode
  /// \treturn \value
  /// \see fold_xs_or_else, fold_right, fold_tree, reverse_fold, fold_balanced_tree
  template<class F, class C = identity>
  using fold_xs = partial_fold_xs_c<-1, F, C>;

  /// As \c fold_xs_or_else, but stop at position \c OffsetEnd.
  template<int_t OffsetEnd, class F, class EmptyC, class C = identity>
  using partial_fold_xs_or_else_c = if_<size<>, partial_fold_xs_c<OffsetEnd, F, C>, EmptyC>;

  template<class OffsetEnd, class F, class NoStateF = F, class C = identity>
  using partial_fold_xs_or_else = partial_fold_xs_or_else_c<OffsetEnd::value, F, NoStateF, C>;

  template<int_t OffsetEnd, class F, class FallbackValue, class C = identity>
  using partial_fold_xs_or_c = partial_fold_xs_or_else_c<OffsetEnd, F, always<FallbackValue>, C>;

  template<class OffsetEnd, class F, class FallbackValue, class C = identity>
  using partial_fold_xs_or = partial_fold_xs_or_else_c<OffsetEnd::value, F, always<FallbackValue>, C>;

  /// Folds left over a list using a mulary predicate.
  /// Like \c fold_xs<>, but uses \c NoStateF when \c xs is empty.
  /// \see fold_xs, fold_right, fold_tree, reverse_fold, fold_balanced_tree
  template<class F, class NoStateF = F, class C = identity>
  using fold_xs_or_else = partial_fold_xs_or_else_c<-1, F, NoStateF, C>;

  template<class F, class FallbackValue, class C = identity>
  using fold_xs_or = partial_fold_xs_or_else_c<-1, F, always<FallbackValue>, C>;

  namespace emp
  {
    template<class L, class OffsetEnd, class state, class F, class C = mp::identity>
    using partial_fold_xs = typename detail::_unpack<
      mp::push_front<state, mp::partial_fold_xs<OffsetEnd, F, C>>, L>::type;

    template<class L, int_t OffsetEnd, class state, class F, class C = mp::identity>
    using partial_fold_xs_c = typename detail::_unpack<
      mp::push_front<state, mp::partial_fold_xs_c<OffsetEnd, F, C>>, L>::type;

    template<class L, class state, class F, class C = mp::identity>
    using fold_xs = typename detail::_unpack<
      mp::push_front<state, mp::partial_fold_xs_c<-1, F, C>>, L>::type;

    template<class L, class OffsetEnd, class F, class NoStateF = F, class C = mp::identity>
    using partial_fold_xs_or_else = typename detail::_unpack<
      mp::partial_fold_xs_or_else<OffsetEnd, F, NoStateF, C>, L>::type;

    template<class L, int_t OffsetEnd, class F, class NoStateF = F, class C = mp::identity>
    using partial_fold_xs_or_else_c = typename detail::_unpack<
      mp::partial_fold_xs_or_else_c<OffsetEnd, F, NoStateF, C>, L>::type;

    template<class L, class F, class NoStateF = F, class C = mp::identity>
    using fold_xs_or_else = typename detail::_unpack<
      mp::partial_fold_xs_or_else_c<-1, F, NoStateF, C>, L>::type;

    template<class L, class OffsetEnd, class F, class FallbackValue, class C = mp::identity>
    using partial_fold_xs_or = typename detail::_unpack<
      mp::partial_fold_xs_or_else<OffsetEnd, F, always<FallbackValue>, C>, L>::type;

    template<class L, int_t OffsetEnd, class F, class FallbackValue, class C = mp::identity>
    using partial_fold_xs_or_c = typename detail::_unpack<
      mp::partial_fold_xs_or_else_c<OffsetEnd, F, always<FallbackValue>, C>, L>::type;

    template<class L, class F, class FallbackValue, class C = mp::identity>
    using fold_xs_or = typename detail::_unpack<
      mp::partial_fold_xs_or_else_c<-1, F, always<FallbackValue>, C>, L>::type;
  }
}


/// \cond
namespace jln::mp
{
  template<int_t OffsetEnd, class F>
  struct partial_fold_xs_c<OffsetEnd, F, identity>
  {
    template<class... xs>
    using f = detail::partial_fold_xs_select<
      JLN_MP_TRACE_F(F)::template f,
      detail::partial_fold_xs_size(OffsetEnd, sizeof...(xs)),
      xs...
    >;
  };

  template<class F, class C>
  struct partial_fold_xs_c<-1, F, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      detail::partial_fold_xs_select<JLN_MP_TRACE_F(F)::template f, sizeof...(xs), xs...>
    );
  };

  template<class F>
  struct partial_fold_xs_c<-1, F, identity>
  {
    template<class... xs>
    using f = detail::partial_fold_xs_select<JLN_MP_TRACE_F(F)::template f, sizeof...(xs), xs...>;
  };

#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_DEBUG
  template<int_t OffsetEnd, template<class...> class F, class C>
  struct partial_fold_xs_c<OffsetEnd, cfe<F>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      detail::partial_fold_xs_select<
        F,
        detail::partial_fold_xs_size(OffsetEnd, sizeof...(xs)),
        xs...
      >
    );
  };

  template<int_t OffsetEnd, template<class...> class F>
  struct partial_fold_xs_c<OffsetEnd, cfe<F>, identity>
  {
    template<class... xs>
    using f = detail::partial_fold_xs_select<
      F,
      detail::partial_fold_xs_size(OffsetEnd, sizeof...(xs)),
      xs...
    >;
  };

  template<template<class...> class F, class C>
  struct partial_fold_xs_c<-1, cfe<F>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      detail::partial_fold_xs_select<F, sizeof...(xs), xs...>
    );
  };

  template<template<class...> class F>
  struct partial_fold_xs_c<-1, cfe<F>, identity>
  {
    template<class... xs>
    using f = detail::partial_fold_xs_select<F, sizeof...(xs), xs...>;
  };
#endif
}

namespace jln::mp::detail
{
  constexpr int_t partial_fold_xs_size(int_t i, int_t size)
  {
    // size contains state + xs...
    return (size == 0) ? 0
      : (i >= size) ? 1
      : (i >= 0) ? i + 1
      : (i >= -size) ? size + i + 1
      : 0
      ;
  }

  template<int n>
  struct fold_xs_impl : fold_xs_impl<
      n < 8 ? 4
    : n < 16 ? 8
    : n < 64 ? 16
    : 64
  >
  {};

  template<>
  struct fold_xs_impl<-1>
  {};

  template<>
  struct fold_xs_impl<0>
  {
    template<template<class...> class, int m, class state>
    using f = state;
  };

  template<>
  struct fold_xs_impl<1>
  {
    template<template<class...> class F, int m, class state, class... xs>
    using f = F<state, xs...>;
  };

  template<>
  struct fold_xs_impl<2>
  {
    template<template<class...> class F, int m, class state,
      class _1, class... xs>
    using f = F<F<state, _1, xs...>, xs...>;
  };

  template<>
  struct fold_xs_impl<3>
  {
    template<template<class...> class F, int m, class state,
      class _1, class _2, class... xs>
    using f = F<F<F<state, _1, _2, xs...>, _2, xs...>, xs...>;
  };

  // newline='\n'
  // for n in (4, 8, 16, 64):
  //   args = ', '.join(f'class _{i}' for i in range(1,n))
  //   ps = [f'_{i}, ' for i in range(1, n)]
  //   print(f'''
  //   template<>
  //   struct fold_xs_impl<{n}>
  //   {{
  //     template<template<class...> class F, int m, class state,
  //       {args}, class... xs>
  //     using f = typename fold_xs_impl<
  //       m-{n-1}
  //     >::template f<F, m-{n-1}, {'F<' * (n-1)}state{''.join(f',{newline}      {"".join(ps[i:])}xs...>' for i in range(n))};
  //   }};
  // ''', end='')

  template<>
  struct fold_xs_impl<4>
  {
    template<template<class...> class F, int m, class state,
      class _1, class _2, class _3, class... xs>
    using f = typename fold_xs_impl<
      m-3
    >::template f<F, m-3, F<F<F<state,
      _1, _2, _3, xs...>,
      _2, _3, xs...>,
      _3, xs...>,
      xs...>;
  };

  template<>
  struct fold_xs_impl<8>
  {
    template<template<class...> class F, int m, class state,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7, class... xs>
    using f = typename fold_xs_impl<
      m-7
    >::template f<F, m-7, F<F<F<F<F<F<F<state,
      _1, _2, _3, _4, _5, _6, _7, xs...>,
      _2, _3, _4, _5, _6, _7, xs...>,
      _3, _4, _5, _6, _7, xs...>,
      _4, _5, _6, _7, xs...>,
      _5, _6, _7, xs...>,
      _6, _7, xs...>,
      _7, xs...>,
      xs...>;
  };

  template<>
  struct fold_xs_impl<16>
  {
    template<template<class...> class F, int m, class state,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11, class _12, class _13, class _14,
      class _15, class... xs>
    using f = typename fold_xs_impl<
      m-15
    >::template f<F, m-15, F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<state,
      _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _9, _10, _11, _12, _13, _14, _15, xs...>,
      _10, _11, _12, _13, _14, _15, xs...>,
      _11, _12, _13, _14, _15, xs...>,
      _12, _13, _14, _15, xs...>,
      _13, _14, _15, xs...>,
      _14, _15, xs...>,
      _15, xs...>,
      xs...>;
  };

  template<>
  struct fold_xs_impl<64>
  {
    template<template<class...> class F, int m, class state,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11, class _12, class _13,
      class _14, class _15, class _16, class _17, class _18, class _19,
      class _20, class _21, class _22, class _23, class _24, class _25,
      class _26, class _27, class _28, class _29, class _30, class _31,
      class _32, class _33, class _34, class _35, class _36, class _37,
      class _38, class _39, class _40, class _41, class _42, class _43,
      class _44, class _45, class _46, class _47, class _48, class _49,
      class _50, class _51, class _52, class _53, class _54, class _55,
      class _56, class _57, class _58, class _59, class _60, class _61,
      class _62, class _63,
      class... xs>
    using f = typename fold_xs_impl<
      m-63
    >::template f<F, m-63, F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<
                           F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<
                           F<F<F<F<F<F<F<F<F<F<F<
      state,
      _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16,
      _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31,
      _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46,
      _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61,
      _62, _63, xs...>,
      _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17,
      _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32,
      _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47,
      _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62,
      _63, xs...>,
      _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18,
      _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33,
      _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48,
      _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63,
      xs...>,
      _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19,
      _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34,
      _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49,
      _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,
      _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35,
      _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,
      _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,
      _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35,
      _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,
      _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21,
      _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36,
      _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51,
      _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22,
      _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37,
      _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52,
      _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23,
      _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38,
      _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53,
      _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24,
      _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39,
      _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54,
      _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25,
      _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40,
      _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55,
      _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26,
      _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41,
      _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
      _57, _58, _59, _60, _61, _62, _63, xs...>,
      _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27,
      _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42,
      _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57,
      _58, _59, _60, _61, _62, _63, xs...>,
      _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28,
      _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43,
      _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58,
      _59, _60, _61, _62, _63, xs...>,
      _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29,
      _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44,
      _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59,
      _60, _61, _62, _63, xs...>,
      _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,
      _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45,
      _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,
      _61, _62, _63, xs...>,
      _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31,
      _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46,
      _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61,
      _62, _63, xs...>,
      _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32,
      _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47,
      _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62,
      _63, xs...>,
      _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33,
      _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48,
      _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63,
      xs...>,
      _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34,
      _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49,
      _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35,
      _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,
      _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36,
      _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51,
      _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37,
      _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52,
      _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38,
      _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53,
      _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39,
      _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54,
      _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40,
      _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55,
      _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41,
      _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
      _57, _58, _59, _60, _61, _62, _63, xs...>,
      _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42,
      _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57,
      _58, _59, _60, _61, _62, _63, xs...>,
      _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43,
      _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58,
      _59, _60, _61, _62, _63, xs...>,
      _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44,
      _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59,
      _60, _61, _62, _63, xs...>,
      _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45,
      _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,
      _61, _62, _63, xs...>,
      _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46,
      _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61,
      _62, _63, xs...>,
      _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47,
      _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62,
      _63, xs...>,
      _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48,
      _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63,
      xs...>,
      _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49,
      _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,
      _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51,
      _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52,
      _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53,
      _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54,
      _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55,
      _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
      _57, _58, _59, _60, _61, _62, _63, xs...>,
      _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57,
      _58, _59, _60, _61, _62, _63, xs...>,
      _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58,
      _59, _60, _61, _62, _63, xs...>,
      _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59,
      _60, _61, _62, _63, xs...>,
      _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,
      _61, _62, _63, xs...>,
      _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61,
      _62, _63, xs...>,
      _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62,
      _63, xs...>,
      _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63,
      xs...>,
      _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _57, _58, _59, _60, _61, _62, _63, xs...>,
      _58, _59, _60, _61, _62, _63, xs...>,
      _59, _60, _61, _62, _63, xs...>,
      _60, _61, _62, _63, xs...>,
      _61, _62, _63, xs...>,
      _62, _63, xs...>,
      _63, xs...>,
      xs...>;
  };
}
/// \endcond
