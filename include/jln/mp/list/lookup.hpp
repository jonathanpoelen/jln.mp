// SPDX-FileCopyrightText: 2026 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/functional/continuation.hpp>
#include <cstddef>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct index;

    constexpr int build_indexed_state(std::size_t n);

#if !(JLN_MP_FEATURE_PACK_INDEXING || JLN_MP_FAST_TYPE_PACK_ELEMENT)
    template<class...>
    struct indexed;

    template<int, bool = false>
    struct indexed_builder;

    template<int, class PrecomputedIndices>
    struct build_indexed_v_impl;

# if JLN_MP_MEMOIZED_ALIAS
    template<int, class PrecomputedIndices>
    struct build_indexed_impl;
# endif
#endif
  }
  /// \endcond

  /// \ingroup list

  /// Constructs an indexable sequence in O(1).
  /// \pre `0 <= i < sizeof...(xs)`
#if JLN_MP_FEATURE_PACK_INDEXING || JLN_MP_FAST_TYPE_PACK_ELEMENT
  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_IGNORE_PACK_INDEXING_EXTENSION()
  template<class... xs>
  struct build_indexed_v
  {
    template<int i>
    using f = JLN_MP_PACK_AT(xs, i);
  };
  JLN_MP_DIAGNOSTIC_POP()
#else
  template<class... xs>
  struct build_indexed_v
  : detail::build_indexed_v_impl<
      detail::build_indexed_state(sizeof...(xs)),
      typename detail::indexed_builder<detail::build_indexed_state(sizeof...(xs))>
      ::template f<xs...>
    >
  {};
#endif

  /// Constructs an indexable sequence in O(1).
  /// If possible prefer the use of build_indexed_v
  /// \pre `0 <= i::value < sizeof...(xs)`
#if JLN_MP_FEATURE_PACK_INDEXING || JLN_MP_FAST_TYPE_PACK_ELEMENT
  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_IGNORE_PACK_INDEXING_EXTENSION()
  template<class... xs>
  struct build_indexed
  {
    template<class i>
    using f = JLN_MP_PACK_AT(xs, i::value);
  };
  JLN_MP_DIAGNOSTIC_POP()
#elif JLN_MP_MEMOIZED_ALIAS
  template<class... xs>
  struct build_indexed
  : detail::build_indexed_impl<
      detail::build_indexed_state(sizeof...(xs)),
      typename detail::indexed_builder<detail::build_indexed_state(sizeof...(xs))>
      ::template f<xs...>
    >
  {
# ifdef JLN_MP_DOXYGENATING
    template<class i>
    using f;
# endif
  };
#else
  template<class... xs>
  struct build_indexed
  {
  private:
    using BuildIndexedV = build_indexed_v<xs...>;

  public:
# if JLN_MP_MEMOIZED_ALIAS
    template<class i>
    using f = typename BuildIndexedV::template f<i::value>;
# else
    template<class i>
    using f = typename BuildIndexedV::template memoize_result_<i::value>::type;
# endif
  };
#endif

  namespace emp
  {
    template<class L>
    using build_indexed_v = typename detail::_unpack<cfe<mp::build_indexed_v>, L>::type;

    template<class L>
    using build_indexed = typename detail::_unpack<cfe<mp::build_indexed>, L>::type;

    template<class L, int i>
    using lookup_c =
      typename detail::_unpack<mp::cfe<mp::build_indexed_v>, L>::type::template f<i>;

    template<class L, class I>
    using lookup =
      typename detail::_unpack<mp::cfe<mp::build_indexed_v>, L>::type::template f<I::value>;

    template<class IndexedV, int i>
    using indexed_lookup_c = typename IndexedV::template f<i>;

    template<class IndexedV, class I>
    using indexed_lookup = typename IndexedV::template f<I::value>;
  }
}


#include <jln/mp/detail/sequence.hpp>
#include <jln/mp/list/list.hpp>

namespace jln::mp::detail
{
  // fast propagation of cfe<build_indexed_v, F> without dependency call
  template<class F>
  struct apply_indexed_v
  {
    template<class... xs>
    using f = typename F::template f<build_indexed_v<xs...>>;
  };


#define JLN_MP_INDEX(n, mp_xs, mp_rxs, mp_dup)      \
  template<>                                        \
  struct index<n-1>                                 \
  {                                                 \
    template<mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL) \
             class... xs>                           \
    using f = _##n;                                 \
  };

  JLN_MP_GEN_XS_1_TO_16_INCLUDED(JLN_MP_INDEX)

#undef JLN_MP_INDEX

  using index0 = index<0>;


#if JLN_MP_FAST_TYPE_PACK_ELEMENT || JLN_MP_FEATURE_PACK_INDEXING
#  define JLN_MP_INDEXED_GET(i, ...) __VA_ARGS__::f<i>
#  define JLN_MP_D_INDEXED_GET(i, ...) __VA_ARGS__::template f<i>
#else
  template<class Head, class Tail>
  struct rlist;

  class unindexed;

  using rlist_tail_of15 =
    rlist<unindexed,
      rlist<unindexed,
        rlist<unindexed,
          rlist<unindexed,
            rlist<unindexed,
              rlist<unindexed,
                rlist<unindexed,
                  rlist<unindexed,
                    rlist<unindexed,
                      rlist<unindexed,
                        rlist<unindexed,
                          rlist<unindexed,
                            rlist<unindexed,
                              rlist<unindexed,
                                rlist<unindexed, unindexed>>>>>>>>>>>>>>>;

  template<class... xs>
  struct indexed
  {
    template<class F>
    using f = typename F::template f<xs...>;
  };

  template<class x>
  struct rlist_to_indexed;

  template<
    class x0, class x1, class x2, class x3, class x4, class x5,
    class x6, class x7, class x8, class x9, class x10, class x11,
    class x12, class x13, class x14, class x15, class Tail>
  struct rlist_to_indexed<
    rlist<x0,
      rlist<x1,
        rlist<x2,
          rlist<x3,
            rlist<x4,
              rlist<x5,
                rlist<x6,
                  rlist<x7,
                    rlist<x8,
                      rlist<x9,
                        rlist<x10,
                          rlist<x11,
                            rlist<x12,
                              rlist<x13,
                                rlist<x14,
                                  rlist<x15, Tail>>>>>>>>>>>>>>>>>
  {
    template<template<class...> class F>
    using f = F<x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15>;
  };


  template<class x>
  struct rlist_to_indexed_rlist;

  template<
    class x0, class x1, class x2, class x3, class x4, class x5,
    class x6, class x7, class x8, class x9, class x10, class x11,
    class x12, class x13, class x14, class x15, class Tail>
  struct rlist_to_indexed_rlist<
    rlist<x0,
      rlist<x1,
        rlist<x2,
          rlist<x3,
            rlist<x4,
              rlist<x5,
                rlist<x6,
                  rlist<x7,
                    rlist<x8,
                      rlist<x9,
                        rlist<x10,
                          rlist<x11,
                            rlist<x12,
                              rlist<x13,
                                rlist<x14,
                                  rlist<x15, Tail>>>>>>>>>>>>>>>>>
  {
    using type = rlist<
      indexed<x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15>,
      typename rlist_to_indexed_rlist<Tail>::type
    >;
  };


  template<
    class x0, class x1, class x2, class x3, class x4, class x5,
    class x6, class x7, class x8, class x9, class x10, class x11,
    class x12, class x13, class x14, class x15, class Tail>
  struct rlist_to_indexed_rlist<
    rlist<x0,
      rlist<x1,
        rlist<x2,
          rlist<x3,
            rlist<x4,
              rlist<x5,
                rlist<x6,
                  rlist<x7,
                    rlist<x8,
                      rlist<x9,
                        rlist<x10,
                          rlist<x11,
                            rlist<x12,
                              rlist<x13,
                                rlist<x14,
                                  rlist<x15,
                                    rlist<unindexed, Tail>>>>>>>>>>>>>>>>>>
  {
    using type = rlist<
      indexed<x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15>,
      rlist_tail_of15
    >;
  };

  template<
    class x0, class x1, class x2, class x3, class x4, class x5,
    class x6, class x7, class x8, class x9, class x10, class x11,
    class x12, class x13, class x14, class x15>
  struct rlist_to_indexed_rlist<
    rlist<x0,
      rlist<x1,
        rlist<x2,
          rlist<x3,
            rlist<x4,
              rlist<x5,
                rlist<x6,
                  rlist<x7,
                    rlist<x8,
                      rlist<x9,
                        rlist<x10,
                          rlist<x11,
                            rlist<x12,
                              rlist<x13,
                                rlist<x14,
                                  rlist<x15, unindexed>>>>>>>>>>>>>>>>>
  {
    using type = rlist<
      indexed<x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15>,
      rlist_tail_of15
    >;
  };


  constexpr int build_indexed_state(std::size_t n)
  {
    return n <= 16 ? 0
         : n <= 256 ? 1
         : n <= 4096 ? 2
         : 3;
  }


  // 0 <= sizeof...(xs) <= 16
  template<>
  struct indexed_builder<0>
    : listify
  {};

  // 16 < sizeof...(xs) <= 256
  template<>
  struct indexed_builder<1>
  {
    template<JLN_MP_XS_256(class, = unindexed, JLN_MP_COMMA)>
    using f = indexed<
      indexed<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12,
              _13, _14, _15, _16>,
      indexed<_17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27,
              _28, _29, _30, _31, _32>,
      indexed<_33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43,
              _44, _45, _46, _47, _48>,
      indexed<_49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59,
              _60, _61, _62, _63, _64>,

      indexed<_65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75,
              _76, _77, _78, _79, _80>,
      indexed<_81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91,
              _92, _93, _94, _95, _96>,
      indexed<_97, _98, _99, _100, _101, _102, _103, _104, _105,
              _106, _107, _108, _109, _110, _111, _112>,
      indexed<_113, _114, _115, _116, _117, _118, _119, _120, _121,
              _122, _123, _124, _125, _126, _127, _128>,

      indexed<_129, _130, _131, _132, _133, _134, _135, _136, _137,
              _138, _139, _140, _141, _142, _143, _144>,
      indexed<_145, _146, _147, _148, _149, _150, _151, _152, _153,
              _154, _155, _156, _157, _158, _159, _160>,
      indexed<_161, _162, _163, _164, _165, _166, _167, _168, _169,
              _170, _171, _172, _173, _174, _175, _176>,
      indexed<_177, _178, _179, _180, _181, _182, _183, _184, _185,
              _186, _187, _188, _189, _190, _191, _192>,

      indexed<_193, _194, _195, _196, _197, _198, _199, _200, _201,
              _202, _203, _204, _205, _206, _207, _208>,
      indexed<_209, _210, _211, _212, _213, _214, _215, _216, _217,
              _218, _219, _220, _221, _222, _223, _224>,
      indexed<_225, _226, _227, _228, _229, _230, _231, _232, _233,
              _234, _235, _236, _237, _238, _239, _240>,
      indexed<_241, _242, _243, _244, _245, _246, _247, _248, _249,
              _250, _251, _252, _253, _254, _255, _256>
    >;
  };

  // 256 < sizeof...(xs) <= 4096
  template<>
  struct indexed_builder<2, false>
  {
    template<JLN_MP_XS_256(class, = unindexed, JLN_MP_COMMA), class... xs>
    using f = rlist<
      indexed<indexed<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12,
                      _13, _14, _15, _16>,
              indexed<_17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27,
                      _28, _29, _30, _31, _32>,
              indexed<_33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43,
                      _44, _45, _46, _47, _48>,
              indexed<_49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59,
                      _60, _61, _62, _63, _64>,

              indexed<_65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75,
                      _76, _77, _78, _79, _80>,
              indexed<_81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91,
                      _92, _93, _94, _95, _96>,
              indexed<_97, _98, _99, _100, _101, _102, _103, _104, _105,
                      _106, _107, _108, _109, _110, _111, _112>,
              indexed<_113, _114, _115, _116, _117, _118, _119, _120, _121,
                      _122, _123, _124, _125, _126, _127, _128>,

              indexed<_129, _130, _131, _132, _133, _134, _135, _136, _137,
                      _138, _139, _140, _141, _142, _143, _144>,
              indexed<_145, _146, _147, _148, _149, _150, _151, _152, _153,
                      _154, _155, _156, _157, _158, _159, _160>,
              indexed<_161, _162, _163, _164, _165, _166, _167, _168, _169,
                      _170, _171, _172, _173, _174, _175, _176>,
              indexed<_177, _178, _179, _180, _181, _182, _183, _184, _185,
                      _186, _187, _188, _189, _190, _191, _192>,

              indexed<_193, _194, _195, _196, _197, _198, _199, _200, _201,
                      _202, _203, _204, _205, _206, _207, _208>,
              indexed<_209, _210, _211, _212, _213, _214, _215, _216, _217,
                      _218, _219, _220, _221, _222, _223, _224>,
              indexed<_225, _226, _227, _228, _229, _230, _231, _232, _233,
                      _234, _235, _236, _237, _238, _239, _240>,
              indexed<_241, _242, _243, _244, _245, _246, _247, _248, _249,
                      _250, _251, _252, _253, _254, _255, _256>>,
      typename indexed_builder<2, sizeof...(xs) <= 16>::template f<xs...>
    >;
  };

  // 256 < sizeof...(xs) <= 4096
  template<>
  struct indexed_builder<2, true>
  {
    template<
      class x0 = unindexed, class x1 = unindexed, class x2 = unindexed, class x3 = unindexed,
      class x4 = unindexed, class x5 = unindexed, class x6 = unindexed, class x7 = unindexed,
      class x8 = unindexed, class x9 = unindexed, class x10 = unindexed, class x11 = unindexed,
      class x12 = unindexed, class x13 = unindexed, class x14 = unindexed, class x15 = unindexed>
    using f = rlist<
      indexed<indexed<x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15>>,
      rlist_tail_of15
    >;
  };

  // 4096 < sizeof...(xs)
  template<>
  struct indexed_builder<3> : indexed_builder<2>
  {};


#if JLN_MP_MEMOIZED_ALIAS
#  define JLN_MP_BUILD_INDEXED_IMPL(impl) template<int i> using f = impl
#  define JLN_MP_INDEXED_GET(i, ...) __VA_ARGS__::f<i>
#  define JLN_MP_D_INDEXED_GET(i, ...) __VA_ARGS__::template f<i>
#else
#  define JLN_MP_BUILD_INDEXED_IMPL(impl)                        \
  template<int i> struct memoize_result_ { using type = impl; }; \
  template<int i> using f = typename memoize_result_<i>::type
#  define JLN_MP_INDEXED_GET(i, ...) __VA_ARGS__::memoize_result_<i>::type
#  define JLN_MP_D_INDEXED_GET(i, ...) __VA_ARGS__::template memoize_result_<i>::type
#endif

  // 0 <= sizeof...(xs) <= 16
  template<class... xs>
  struct build_indexed_v_impl<0, list<xs...>>
  {
    JLN_MP_BUILD_INDEXED_IMPL(typename index<i>::template f<xs...>);
  };

  // 16 < sizeof...(xs) <= 256
  template<class PrecomputedIndices>
  struct build_indexed_v_impl<1, PrecomputedIndices>
  {
    JLN_MP_BUILD_INDEXED_IMPL(
      typename PrecomputedIndices
      ::template f<index<(i >> 4)>>
      ::template f<index<i & 0xf>>
    );
  };

  // 256 < sizeof...(xs) <= 4096
  template<class PrecomputedIndices>
  struct build_indexed_v_impl<2, PrecomputedIndices>
  {
  private:
    using _precomputed_indices = typename rlist_to_indexed<PrecomputedIndices>
      ::template f<indexed>;

  public:
    JLN_MP_BUILD_INDEXED_IMPL(
      typename _precomputed_indices
      ::template f<index<(i >> 8)>>
      ::template f<index<(i >> 4) & 0xF>>
      ::template f<index<(i & 0xF)>>
    );
  };

  // 4096 < sizeof...(xs) <= 65536
  template<class PrecomputedIndices>
  struct build_indexed_v_impl<3, PrecomputedIndices>
  {
  private:
    using _precomputed_indices = typename rlist_to_indexed<
      typename rlist_to_indexed_rlist<PrecomputedIndices>::type
    >::template f<indexed>;

  public:
    JLN_MP_BUILD_INDEXED_IMPL(
      typename _precomputed_indices
      ::template f<index<(i >> 12)>>
      ::template f<index<(i >> 8) & 0xF>>
      ::template f<index<(i >> 4) & 0xF>>
      ::template f<index<(i & 0xF)>>
    );
  };

#undef JLN_MP_BUILD_INDEXED_IMPL

# if JLN_MP_MEMOIZED_ALIAS
  // 0 <= sizeof...(xs) <= 16
  template<class... xs>
  struct build_indexed_impl<0, list<xs...>>
  {
    template<class i>
    using f = typename index<i::value>::template f<xs...>;
  };

  // 16 < sizeof...(xs) <= 256
  template<class PrecomputedIndices>
  struct build_indexed_impl<1, PrecomputedIndices>
  {
    template<class i>
    using f = typename PrecomputedIndices
      ::template f<index<(i::value >> 4)>>
      ::template f<index<i::value & 0xf>>;
  };

  // 256 < sizeof...(xs) <= 4096
  template<class PrecomputedIndices>
  class build_indexed_impl<2, PrecomputedIndices>
  {
    using _precomputed_indices = typename rlist_to_indexed<PrecomputedIndices>
      ::template f<indexed>;

  public:
    template<class i>
    using f = typename _precomputed_indices
      ::template f<index<(i::value >> 8)>>
      ::template f<index<(i::value >> 4) & 0xF>>
      ::template f<index<i::value & 0xF>>;
  };

  // 4096 < sizeof...(xs) <= 65536
  template<class PrecomputedIndices>
  class build_indexed_impl<3, PrecomputedIndices>
  {
    using _precomputed_indices = typename rlist_to_indexed<
      typename rlist_to_indexed_rlist<PrecomputedIndices>::type
    >::template f<indexed>;

  public:
    template<class i>
    using f = typename _precomputed_indices
      ::template f<index<(i::value >> 12)>>
      ::template f<index<(i::value >> 8) & 0xF>>
      ::template f<index<(i::value >> 4) & 0xF>>
      ::template f<index<i::value & 0xF>>;
  };
#endif

#endif

}
