#pragma once

#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <jln/mp/list/lookup.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct arrange_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Uses a list of indexes to reorder a sequence.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   arrange<numbers<0, 2, 0>>::f<a, b, c, d> == list<a, c, a>
  ///   \endcode
  /// \treturn \list
  template<class Ints, class C = listify>
  struct arrange
  {};

  template<unsigned... ints>
  using arrange_c = arrange<int_seq_v<ints...>>;

  template<int_... ints, class C>
  struct arrange<int_seq_v<ints...>, C>
  {
    template<class... xs>
    using f = typename detail::arrange_impl<sizeof...(xs) < 4096>
      ::template f<C, build_indexed<>::f<xs...>, ints...>;
  };

  template<template<class...> class Tpl, class... ints, class C>
  struct arrange<Tpl<ints...>, C>
    : arrange<int_seq_v<ints::value...>, C>
  {};

  template<template<class T, T...> class Tpl, class T, T... ints, class C>
  struct arrange<Tpl<T, ints...>, C>
    : arrange<int_seq_v<ints...>, C>
  {};

  namespace emp
  {
    template<class L, class Ints, class C = listify>
    using arrange = unpack<L, mp::arrange<Ints, C>>;

    template<class L, unsigned... ints>
    using arrange_c = unpack<L, mp::arrange<int_seq_v<ints...>>>;
  }
}

namespace jln::mp::detail
{
  template<class Indexed>
  struct indexed_tail;

  template<
    class x0, class x1, class x2, class x3, class x4, class x5,
    class x6, class x7, class x8, class x9, class x10, class x11,
    class x12, class x13, class x14, class x15, class Tail>
  struct indexed_tail<indexed<
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
                                  rlist<x15, Tail>>>>>>>>>>>>>>>>>>
  {
    using type = indexed<Tail>;
  };

  template<bool>
  struct arrange_select;

  template<>
  struct arrange_select<true>
  {
    template<class PrecomputedIndexes, unsigned i>
    using f = emp::precomputed_indexes_at_c<PrecomputedIndexes, i>;
  };

  template<>
  struct arrange_select<false>
  {
    template<class PrecomputedIndexes, unsigned i>
    using f = typename arrange_select<i < 8192>
      ::template f<typename indexed_tail<PrecomputedIndexes>::type, i - 4096>;
  };

  template<>
  struct arrange_impl<false>
  {
    template<class C, class PrecomputedIndexes, unsigned... ints>
    using f = JLN_MP_DCALL_TRACE_XS(ints, C,
      typename arrange_select<ints < 4096>::template f<PrecomputedIndexes, ints>
    ...);
  };

  template<>
  struct arrange_impl<true>
  {
    template<class C, class PrecomputedIndexes, unsigned... ints>
    using f = JLN_MP_DCALL_TRACE_XS(ints, C, emp::precomputed_indexes_at_c<
      PrecomputedIndexes, ints
    >...);
  };
}
