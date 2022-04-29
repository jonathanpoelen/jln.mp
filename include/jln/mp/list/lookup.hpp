#pragma once

// This implementation comes from kvasir.mpl

#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/functional/identity.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned>
    struct index;

    template<class...>
    struct indexed;

    template<int>
    struct indexed_builder;
  }
  /// \endcond

  /// \ingroup list

  template<class C = identity>
  struct build_indexed
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, detail::indexed<
      typename detail::indexed_builder<16 < sizeof...(xs) ? 3 : 1>
      ::template f<xs...>
    >);
  };

  /// \cond
  template<>
  struct build_indexed<identity>
  {
    template<class... xs>
    using f = detail::indexed<
      typename detail::indexed_builder<16 < sizeof...(xs) ? 3 : 1>
      ::template f<xs...>
    >;
  };
  /// \endcond

  template<class L, class C = identity>
  struct lookup
  {};

  template<template<class...> class Seq, class... xs, class C>
  struct lookup<Seq<xs...>, C>
  {
    template<class i>
    using f = JLN_MP_CALL_TRACE(C, typename build_indexed<>::f<xs...>
      ::template f<detail::index<(i::value >> 8)>>
      ::template f<detail::index<((i::value >> 4) & 0xF)>>
      ::template f<detail::index<(i::value & 0xF)>>
    );
  };

  /// \cond
  template<template<class...> class Seq, class... xs>
  struct lookup<Seq<xs...>, identity>
  {
    template<class i>
    using f = typename build_indexed<>::f<xs...>
      ::template f<detail::index<(i::value >> 8)>>
      ::template f<detail::index<((i::value >> 4) & 0xF)>>
      ::template f<detail::index<(i::value & 0xF)>>;
  };
  /// \endcond

  template<unsigned i, class C = identity>
  struct precomputed_indexes_at_c
  {
    template<class PrecomputedIndexes>
    using f = typename C::template f<typename PrecomputedIndexes
      ::template f<detail::index<(i >> 8)>>
      ::template f<detail::index<((i >> 4) & 0xF)>>
      ::template f<detail::index<(i & 0xF)>>
    >;
  };

  /// \cond
  template<unsigned i>
  struct precomputed_indexes_at_c<i, identity>
  {
    template<class PrecomputedIndexes>
    using f = typename PrecomputedIndexes
      ::template f<detail::index<(i >> 8)>>
      ::template f<detail::index<((i >> 4) & 0xF)>>
      ::template f<detail::index<(i & 0xF)>>;
  };
  /// \endcond

  template<class I, class C = identity>
  using precomputed_indexes_at = precomputed_indexes_at_c<I::value, C>;

  namespace emp
  {
    template<class... xs>
    using build_indexed_for = mp::build_indexed<>::f<xs...>;

    template<class L, class C = mp::identity>
    using build_indexed = unpack<L, mp::build_indexed<C>>;

    template<class PrecomputedIndexes, unsigned i>
    using precomputed_indexes_at_c = typename PrecomputedIndexes
      ::template f<detail::index<(i >> 8)>>
      ::template f<detail::index<((i >> 4) & 0xF)>>
      ::template f<detail::index<(i & 0xF)>>;

    template<class PrecomputedIndexes, class I>
    using precomputed_indexes_at = precomputed_indexes_at_c<PrecomputedIndexes, I::value>;

    template<class L, unsigned i>
    using lookup_c = precomputed_indexes_at_c<unpack<L, mp::build_indexed<>>, i>;

    template<class L, class I>
    using lookup = precomputed_indexes_at_c<unpack<L, mp::build_indexed<>>, I::value>;
  }
}


#include <jln/mp/detail/enumerate.hpp>
#include <jln/mp/list/list.hpp>

namespace jln::mp::detail
{
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

  template<class Head, class Tail>
  struct rlist;

  class unindexed;

  using rlist_tail_of15 =
    rlist<list<>,
      rlist<list<>,
        rlist<list<>,
          rlist<list<>,
            rlist<list<>,
              rlist<list<>,
                rlist<list<>,
                  rlist<list<>,
                    rlist<list<>,
                      rlist<list<>,
                        rlist<list<>,
                          rlist<list<>,
                            rlist<list<>,
                              rlist<list<>,
                                rlist<list<>, unindexed>>>>>>>>>>>>>>>;

  using rlist_tail_of16 = rlist<list<>, rlist_tail_of15>;

  template<class... xs>
  struct indexed
  {
    template<class F>
    using f = typename F::template f<xs...>;
  };

  template<
    class x0, class x1, class x2, class x3, class x4, class x5,
    class x6, class x7, class x8, class x9, class x10, class x11,
    class x12, class x13, class x14, class x15, class Tail>
  struct indexed<
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
    template<class F>
    using f = typename F::template f<
      x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15
    >;
  };

  template<>
  struct indexed_builder<0>
  {
    template<class...>
    using f = rlist_tail_of16;
  };

  template<>
  struct indexed_builder<1>
  {
    template<
      class x0 = unindexed, class x1 = unindexed, class x2 = unindexed, class x3 = unindexed,
      class x4 = unindexed, class x5 = unindexed, class x6 = unindexed, class x7 = unindexed,
      class x8 = unindexed, class x9 = unindexed, class x10 = unindexed, class x11 = unindexed,
      class x12 = unindexed, class x13 = unindexed, class x14 = unindexed, class x15 = unindexed,
      class...>
    using f = rlist<
      indexed<indexed<x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15>>,
      rlist_tail_of15
    >;
  };

  template<>
  struct indexed_builder<3>
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
      typename indexed_builder<16 < sizeof...(xs) ? 3 : 1>::template f<xs...>
    >;
  };
}
