// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/reverse.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class F, class C>
    struct scan_right_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Fold a \sequence to the right and return a list containing the successive reduction states.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   C::f<
  ///     ...
  ///     F::f<xs[n-3], F::f<xs[n-2], xs[n-1]>>,
  ///     F::f<xs[n-2], xs[n-1]>,
  ///     xs[n-1],
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class F, class C = listify>
  using scan_right = reverse<detail::scan_right_impl<F, C>>;

  namespace emp
  {
    template<class L, class F, class C = mp::listify>
    using scan_right = typename detail::_unpack<mp::scan_right<F, C>, L>::type;
  }
}


#include <jln/mp/algorithm/scan.hpp> // scan_continuation

/// \cond
namespace jln::mp::detail
{
  template<unsigned n>
  struct _scan_right : _scan_right<
      n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : n <= 128 ? 128
    : 256
  >
  {};

  template<unsigned>
  struct _scan_right;

  template<class F, class C>
  struct scan_right_impl
  {
    template<class... xs>
    using f = typename _scan_right<sizeof...(xs)>
    ::template f<sizeof...(xs), C, JLN_MP_TRACE_F(F)::template f, xs...>;
  };

  template<>
  struct _scan_right<0>
  {
    template<unsigned remaining, class C, template<class...> class F,
      class... xs>
    using f = typename join<C>::template f<xs...>;
  };

  template<>
  struct _scan_right<1>
  {
    template<unsigned remaining, class C, template<class...> class F,
      class _0, class... xs>
    using f = typename join<C>::template f<list<_0>, xs...>;
  };

  template<>
  struct _scan_right<2>
  {
    template<unsigned remaining, class C, template<class...> class F,
      class _0, class _1, class... xs>
    using f = typename join<C>::template f<list<F<_1, _0>, _0>, xs...>;
  };

  // for n in range(3,9):
  //   args=', '.join(f'class _{i}' for i in range(1,n))
  //   ps=', '.join(f'_{i}' for i in range(n))
  //   rs=', '.join(f'class r{i} = F<_{i}, r{i-1}>' for i in range(1, n-1))
  //   l=', '.join(f'r{i}' for i in range(n-2, -1, -1))
  //   sep=', ' if n > 2 else ''
  //   print(f'''
  //   template<>
  //   struct _scan_right<{n}>
  //   {{
  //     template<template<class...> class F,
  //       class r0, {args}{sep}{rs}>
  //     using g = list<F<_{n-1}, r{n-2}>, {l}>;
  //
  //     template<unsigned remaining, class C, template<class...> class F,
  //       class _0, {args}, class... xs>
  //     using f = typename join<C>::template f<g<F, {ps}>, xs...>;
  //   }};''')

  template<>
  struct _scan_right<3>
  {
    template<template<class...> class F, class r0, class _1, class _2,
             class r1 = F<_1, r0>>
    using g = list<F<_2, r1>, r1, r0>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class... xs>
    using f = typename join<C>::template f<xs..., g<F, _0, _1, _2>>;
  };

  template<>
  struct _scan_right<4>
  {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
              class r1 = F<_1, r0>, class r2 = F<_2, r1>>
    using g = list<F<_3, r2>, r2, r1, r0>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class... xs>
    using f = typename join<C>::template f<g<F, _0, _1, _2, _3>, xs...>;
  };

  template<>
  struct _scan_right<5>
  {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
             class _4, class r1 = F<_1, r0>, class r2 = F<_2, r1>,
             class r3 = F<_3, r2>>
    using g = list<F<_4, r3>, r3, r2, r1, r0>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class... xs>
    using f = typename join<C>::template f<g<F, _0, _1, _2, _3, _4>, xs...>;
  };

  template<>
  struct _scan_right<6>
  {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
             class _4, class _5, class r1 = F<_1, r0>, class r2 = F<_2, r1>,
             class r3 = F<_3, r2>, class r4 = F<_4, r3>>
    using g = list<F<_5, r4>, r4, r3, r2, r1, r0>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
              class _1, class _2, class _3, class _4, class _5, class... xs>
    using f = typename join<C>::template f<g<F, _0, _1, _2, _3, _4, _5>, xs...>;
  };

  template<>
  struct _scan_right<7>
  {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
             class _4, class _5, class _6, class r1 = F<_1, r0>,
             class r2 = F<_2, r1>, class r3 = F<_3, r2>, class r4 = F<_4, r3>,
             class r5 = F<_5, r4>>
    using g = list<F<_6, r5>, r5, r4, r3, r2, r1, r0>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class _5, class _6,
             class... xs>
    using f = typename join<C>::template f<g<F, _0, _1, _2, _3, _4, _5, _6>, xs...>;
  };

  template<>
  struct _scan_right<8>
  {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
             class _4, class _5, class _6, class _7, class r1 = F<_1, r0>,
             class r2 = F<_2, r1>, class r3 = F<_3, r2>, class r4 = F<_4, r3>,
             class r5 = F<_5, r4>, class r6 = F<_6, r5>>
    using g = list<F<_7, r6>, r6, r5, r4, r3, r2, r1, r0>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class _5, class _6,
             class _7, class... xs>
    using f = typename join<C>::template f<g<F, _0, _1, _2, _3, _4, _5, _6, _7>, xs...>;
  };

  // for n in [8,16,32,64,128]:
  //   args=', '.join(f'class _{i}' for i in range(1, n))
  //   ps=', '.join(f'_{i}' for i in range(n))
  //   rs=', '.join(f'class r{i} = F<_{i}, r{i-1}>' for i in range(1, n-1))
  //   l=', '.join(f'r{i}' for i in range(n-2,-1,-1))
  //   print(f'''
  //   template<>
  //   struct _scan_right<{n*2}>
  //   {{
  //     template<template<class...> class F,
  //       class r0, {args},
  //       {rs}>
  //     using g = scan_continuation<F<_{n-1}, r{n-2}>, list<{l}>>;
  //
  //     template<unsigned remaining, class C, template<class...> class F,
  //       class _0, {args},
  //       class... xs>
  //     using f = typename g<F, {ps}>
  //       ::template f<remaining-{n-1}, _scan_right<remaining-{n-1}>, C, F, xs..
  // .>;
  //   }};''')

  template<> struct _scan_right<16>
  {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
             class _4, class _5, class _6, class _7, class r1 = F<_1, r0>,
             class r2 = F<_2, r1>, class r3 = F<_3, r2>, class r4 = F<_4, r3>,
             class r5 = F<_5, r4>, class r6 = F<_6, r5>>
    using g = scan_continuation<F<_7, r6>, list<r6, r5, r4, r3, r2, r1, r0>>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class _5, class _6,
             class _7, class... xs>
    using f = typename g<F, _0, _1, _2, _3, _4, _5, _6, _7>::template f<
        remaining - 7, _scan_right<remaining - 7>, C, F, xs...>;
  };

  template<> struct _scan_right<32> {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
             class _4, class _5, class _6, class _7, class _8, class _9,
             class _10, class _11, class _12, class _13, class _14, class _15,
             class r1 = F<_1, r0>, class r2 = F<_2, r1>, class r3 = F<_3, r2>,
             class r4 = F<_4, r3>, class r5 = F<_5, r4>, class r6 = F<_6, r5>,
             class r7 = F<_7, r6>, class r8 = F<_8, r7>, class r9 = F<_9, r8>,
             class r10 = F<_10, r9>, class r11 = F<_11, r10>,
             class r12 = F<_12, r11>, class r13 = F<_13, r12>,
             class r14 = F<_14, r13>>
    using g =
        scan_continuation<F<_15, r14>, list<r14, r13, r12, r11, r10, r9, r8, r7,
                                            r6, r5, r4, r3, r2, r1, r0>>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class _5, class _6,
             class _7, class _8, class _9, class _10, class _11, class _12,
             class _13, class _14, class _15, class... xs>
    using f = typename g<F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12,
                         _13, _14, _15>::
        template f<remaining - 15, _scan_right<remaining - 15>, C, F, xs...>;
  };

  template<> struct _scan_right<64> {
    template<
        template<class...> class F, class r0, class _1, class _2, class _3,
        class _4, class _5, class _6, class _7, class _8, class _9, class _10,
        class _11, class _12, class _13, class _14, class _15, class _16,
        class _17, class _18, class _19, class _20, class _21, class _22,
        class _23, class _24, class _25, class _26, class _27, class _28,
        class _29, class _30, class _31, class r1 = F<_1, r0>,
        class r2 = F<_2, r1>, class r3 = F<_3, r2>, class r4 = F<_4, r3>,
        class r5 = F<_5, r4>, class r6 = F<_6, r5>, class r7 = F<_7, r6>,
        class r8 = F<_8, r7>, class r9 = F<_9, r8>, class r10 = F<_10, r9>,
        class r11 = F<_11, r10>, class r12 = F<_12, r11>, class r13 = F<_13, r12>,
        class r14 = F<_14, r13>, class r15 = F<_15, r14>, class r16 = F<_16, r15>,
        class r17 = F<_17, r16>, class r18 = F<_18, r17>, class r19 = F<_19, r18>,
        class r20 = F<_20, r19>, class r21 = F<_21, r20>, class r22 = F<_22, r21>,
        class r23 = F<_23, r22>, class r24 = F<_24, r23>, class r25 = F<_25, r24>,
        class r26 = F<_26, r25>, class r27 = F<_27, r26>, class r28 = F<_28, r27>,
        class r29 = F<_29, r28>, class r30 = F<_30, r29>>
    using g =
        scan_continuation<F<_31, r30>,
                          list<r30, r29, r28, r27, r26, r25, r24, r23, r22, r21,
                               r20, r19, r18, r17, r16, r15, r14, r13, r12, r11,
                               r10, r9, r8, r7, r6, r5, r4, r3, r2, r1, r0>>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class _5, class _6,
             class _7, class _8, class _9, class _10, class _11, class _12,
             class _13, class _14, class _15, class _16, class _17, class _18,
             class _19, class _20, class _21, class _22, class _23, class _24,
             class _25, class _26, class _27, class _28, class _29, class _30,
             class _31, class... xs>
    using f = typename g<F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12,
                         _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23,
                         _24, _25, _26, _27, _28, _29, _30, _31>::
        template f<remaining - 31, _scan_right<remaining - 31>, C, F, xs...>;
  };

  template<> struct _scan_right<128> {
    template<
        template<class...> class F, class r0, class _1, class _2, class _3,
        class _4, class _5, class _6, class _7, class _8, class _9, class _10,
        class _11, class _12, class _13, class _14, class _15, class _16,
        class _17, class _18, class _19, class _20, class _21, class _22,
        class _23, class _24, class _25, class _26, class _27, class _28,
        class _29, class _30, class _31, class _32, class _33, class _34,
        class _35, class _36, class _37, class _38, class _39, class _40,
        class _41, class _42, class _43, class _44, class _45, class _46,
        class _47, class _48, class _49, class _50, class _51, class _52,
        class _53, class _54, class _55, class _56, class _57, class _58,
        class _59, class _60, class _61, class _62, class _63,
        class r1 = F<_1, r0>, class r2 = F<_2, r1>, class r3 = F<_3, r2>,
        class r4 = F<_4, r3>, class r5 = F<_5, r4>, class r6 = F<_6, r5>,
        class r7 = F<_7, r6>, class r8 = F<_8, r7>, class r9 = F<_9, r8>,
        class r10 = F<_10, r9>, class r11 = F<_11, r10>, class r12 = F<_12, r11>,
        class r13 = F<_13, r12>, class r14 = F<_14, r13>, class r15 = F<_15, r14>,
        class r16 = F<_16, r15>, class r17 = F<_17, r16>, class r18 = F<_18, r17>,
        class r19 = F<_19, r18>, class r20 = F<_20, r19>, class r21 = F<_21, r20>,
        class r22 = F<_22, r21>, class r23 = F<_23, r22>, class r24 = F<_24, r23>,
        class r25 = F<_25, r24>, class r26 = F<_26, r25>, class r27 = F<_27, r26>,
        class r28 = F<_28, r27>, class r29 = F<_29, r28>, class r30 = F<_30, r29>,
        class r31 = F<_31, r30>, class r32 = F<_32, r31>, class r33 = F<_33, r32>,
        class r34 = F<_34, r33>, class r35 = F<_35, r34>, class r36 = F<_36, r35>,
        class r37 = F<_37, r36>, class r38 = F<_38, r37>, class r39 = F<_39, r38>,
        class r40 = F<_40, r39>, class r41 = F<_41, r40>, class r42 = F<_42, r41>,
        class r43 = F<_43, r42>, class r44 = F<_44, r43>, class r45 = F<_45, r44>,
        class r46 = F<_46, r45>, class r47 = F<_47, r46>, class r48 = F<_48, r47>,
        class r49 = F<_49, r48>, class r50 = F<_50, r49>, class r51 = F<_51, r50>,
        class r52 = F<_52, r51>, class r53 = F<_53, r52>, class r54 = F<_54, r53>,
        class r55 = F<_55, r54>, class r56 = F<_56, r55>, class r57 = F<_57, r56>,
        class r58 = F<_58, r57>, class r59 = F<_59, r58>, class r60 = F<_60, r59>,
        class r61 = F<_61, r60>, class r62 = F<_62, r61>>
    using g = scan_continuation<
        F<_63, r62>,
        list<r62, r61, r60, r59, r58, r57, r56, r55, r54, r53, r52, r51, r50, r49,
             r48, r47, r46, r45, r44, r43, r42, r41, r40, r39, r38, r37, r36, r35,
             r34, r33, r32, r31, r30, r29, r28, r27, r26, r25, r24, r23, r22, r21,
             r20, r19, r18, r17, r16, r15, r14, r13, r12, r11, r10, r9, r8, r7,
             r6, r5, r4, r3, r2, r1, r0>>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class _5, class _6,
             class _7, class _8, class _9, class _10, class _11, class _12,
             class _13, class _14, class _15, class _16, class _17, class _18,
             class _19, class _20, class _21, class _22, class _23, class _24,
             class _25, class _26, class _27, class _28, class _29, class _30,
             class _31, class _32, class _33, class _34, class _35, class _36,
             class _37, class _38, class _39, class _40, class _41, class _42,
             class _43, class _44, class _45, class _46, class _47, class _48,
             class _49, class _50, class _51, class _52, class _53, class _54,
             class _55, class _56, class _57, class _58, class _59, class _60,
             class _61, class _62, class _63, class... xs>
    using f = typename g<F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12,
                         _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23,
                         _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34,
                         _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45,
                         _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
                         _57, _58, _59, _60, _61, _62, _63>::
        template f<remaining - 63, _scan_right<remaining - 63>, C, F, xs...>;
  };

  template<> struct _scan_right<256> {
    template<
        template<class...> class F, class r0, class _1, class _2, class _3,
        class _4, class _5, class _6, class _7, class _8, class _9, class _10,
        class _11, class _12, class _13, class _14, class _15, class _16,
        class _17, class _18, class _19, class _20, class _21, class _22,
        class _23, class _24, class _25, class _26, class _27, class _28,
        class _29, class _30, class _31, class _32, class _33, class _34,
        class _35, class _36, class _37, class _38, class _39, class _40,
        class _41, class _42, class _43, class _44, class _45, class _46,
        class _47, class _48, class _49, class _50, class _51, class _52,
        class _53, class _54, class _55, class _56, class _57, class _58,
        class _59, class _60, class _61, class _62, class _63, class _64,
        class _65, class _66, class _67, class _68, class _69, class _70,
        class _71, class _72, class _73, class _74, class _75, class _76,
        class _77, class _78, class _79, class _80, class _81, class _82,
        class _83, class _84, class _85, class _86, class _87, class _88,
        class _89, class _90, class _91, class _92, class _93, class _94,
        class _95, class _96, class _97, class _98, class _99, class _100,
        class _101, class _102, class _103, class _104, class _105, class _106,
        class _107, class _108, class _109, class _110, class _111, class _112,
        class _113, class _114, class _115, class _116, class _117, class _118,
        class _119, class _120, class _121, class _122, class _123, class _124,
        class _125, class _126, class _127, class r1 = F<_1, r0>,
        class r2 = F<_2, r1>, class r3 = F<_3, r2>, class r4 = F<_4, r3>,
        class r5 = F<_5, r4>, class r6 = F<_6, r5>, class r7 = F<_7, r6>,
        class r8 = F<_8, r7>, class r9 = F<_9, r8>, class r10 = F<_10, r9>,
        class r11 = F<_11, r10>, class r12 = F<_12, r11>, class r13 = F<_13, r12>,
        class r14 = F<_14, r13>, class r15 = F<_15, r14>, class r16 = F<_16, r15>,
        class r17 = F<_17, r16>, class r18 = F<_18, r17>, class r19 = F<_19, r18>,
        class r20 = F<_20, r19>, class r21 = F<_21, r20>, class r22 = F<_22, r21>,
        class r23 = F<_23, r22>, class r24 = F<_24, r23>, class r25 = F<_25, r24>,
        class r26 = F<_26, r25>, class r27 = F<_27, r26>, class r28 = F<_28, r27>,
        class r29 = F<_29, r28>, class r30 = F<_30, r29>, class r31 = F<_31, r30>,
        class r32 = F<_32, r31>, class r33 = F<_33, r32>, class r34 = F<_34, r33>,
        class r35 = F<_35, r34>, class r36 = F<_36, r35>, class r37 = F<_37, r36>,
        class r38 = F<_38, r37>, class r39 = F<_39, r38>, class r40 = F<_40, r39>,
        class r41 = F<_41, r40>, class r42 = F<_42, r41>, class r43 = F<_43, r42>,
        class r44 = F<_44, r43>, class r45 = F<_45, r44>, class r46 = F<_46, r45>,
        class r47 = F<_47, r46>, class r48 = F<_48, r47>, class r49 = F<_49, r48>,
        class r50 = F<_50, r49>, class r51 = F<_51, r50>, class r52 = F<_52, r51>,
        class r53 = F<_53, r52>, class r54 = F<_54, r53>, class r55 = F<_55, r54>,
        class r56 = F<_56, r55>, class r57 = F<_57, r56>, class r58 = F<_58, r57>,
        class r59 = F<_59, r58>, class r60 = F<_60, r59>, class r61 = F<_61, r60>,
        class r62 = F<_62, r61>, class r63 = F<_63, r62>, class r64 = F<_64, r63>,
        class r65 = F<_65, r64>, class r66 = F<_66, r65>, class r67 = F<_67, r66>,
        class r68 = F<_68, r67>, class r69 = F<_69, r68>, class r70 = F<_70, r69>,
        class r71 = F<_71, r70>, class r72 = F<_72, r71>, class r73 = F<_73, r72>,
        class r74 = F<_74, r73>, class r75 = F<_75, r74>, class r76 = F<_76, r75>,
        class r77 = F<_77, r76>, class r78 = F<_78, r77>, class r79 = F<_79, r78>,
        class r80 = F<_80, r79>, class r81 = F<_81, r80>, class r82 = F<_82, r81>,
        class r83 = F<_83, r82>, class r84 = F<_84, r83>, class r85 = F<_85, r84>,
        class r86 = F<_86, r85>, class r87 = F<_87, r86>, class r88 = F<_88, r87>,
        class r89 = F<_89, r88>, class r90 = F<_90, r89>, class r91 = F<_91, r90>,
        class r92 = F<_92, r91>, class r93 = F<_93, r92>, class r94 = F<_94, r93>,
        class r95 = F<_95, r94>, class r96 = F<_96, r95>, class r97 = F<_97, r96>,
        class r98 = F<_98, r97>, class r99 = F<_99, r98>,
        class r100 = F<_100, r99>, class r101 = F<_101, r100>,
        class r102 = F<_102, r101>, class r103 = F<_103, r102>,
        class r104 = F<_104, r103>, class r105 = F<_105, r104>,
        class r106 = F<_106, r105>, class r107 = F<_107, r106>,
        class r108 = F<_108, r107>, class r109 = F<_109, r108>,
        class r110 = F<_110, r109>, class r111 = F<_111, r110>,
        class r112 = F<_112, r111>, class r113 = F<_113, r112>,
        class r114 = F<_114, r113>, class r115 = F<_115, r114>,
        class r116 = F<_116, r115>, class r117 = F<_117, r116>,
        class r118 = F<_118, r117>, class r119 = F<_119, r118>,
        class r120 = F<_120, r119>, class r121 = F<_121, r120>,
        class r122 = F<_122, r121>, class r123 = F<_123, r122>,
        class r124 = F<_124, r123>, class r125 = F<_125, r124>,
        class r126 = F<_126, r125>>
    using g = scan_continuation<
        F<_127, r126>,
        list<r126, r125, r124, r123, r122, r121, r120, r119, r118, r117, r116,
             r115, r114, r113, r112, r111, r110, r109, r108, r107, r106, r105,
             r104, r103, r102, r101, r100, r99, r98, r97, r96, r95, r94, r93, r92,
             r91, r90, r89, r88, r87, r86, r85, r84, r83, r82, r81, r80, r79, r78,
             r77, r76, r75, r74, r73, r72, r71, r70, r69, r68, r67, r66, r65, r64,
             r63, r62, r61, r60, r59, r58, r57, r56, r55, r54, r53, r52, r51, r50,
             r49, r48, r47, r46, r45, r44, r43, r42, r41, r40, r39, r38, r37, r36,
             r35, r34, r33, r32, r31, r30, r29, r28, r27, r26, r25, r24, r23, r22,
             r21, r20, r19, r18, r17, r16, r15, r14, r13, r12, r11, r10, r9, r8,
             r7, r6, r5, r4, r3, r2, r1, r0>>;

    template<
        unsigned remaining, class C, template<class...> class F, class _0,
        class _1, class _2, class _3, class _4, class _5, class _6, class _7,
        class _8, class _9, class _10, class _11, class _12, class _13, class _14,
        class _15, class _16, class _17, class _18, class _19, class _20,
        class _21, class _22, class _23, class _24, class _25, class _26,
        class _27, class _28, class _29, class _30, class _31, class _32,
        class _33, class _34, class _35, class _36, class _37, class _38,
        class _39, class _40, class _41, class _42, class _43, class _44,
        class _45, class _46, class _47, class _48, class _49, class _50,
        class _51, class _52, class _53, class _54, class _55, class _56,
        class _57, class _58, class _59, class _60, class _61, class _62,
        class _63, class _64, class _65, class _66, class _67, class _68,
        class _69, class _70, class _71, class _72, class _73, class _74,
        class _75, class _76, class _77, class _78, class _79, class _80,
        class _81, class _82, class _83, class _84, class _85, class _86,
        class _87, class _88, class _89, class _90, class _91, class _92,
        class _93, class _94, class _95, class _96, class _97, class _98,
        class _99, class _100, class _101, class _102, class _103, class _104,
        class _105, class _106, class _107, class _108, class _109, class _110,
        class _111, class _112, class _113, class _114, class _115, class _116,
        class _117, class _118, class _119, class _120, class _121, class _122,
        class _123, class _124, class _125, class _126, class _127, class... xs>
    using f = typename g<
        F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15,
        _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,
        _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45,
        _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,
        _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75,
        _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90,
        _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104,
        _105, _106, _107, _108, _109, _110, _111, _112, _113, _114, _115, _116,
        _117, _118, _119, _120, _121, _122, _123, _124, _125, _126, _127>::
        template f<remaining - 127, _scan_right<remaining - 127>, C, F, xs...>;
  };
}
/// \endcond
