// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/number/operators.hpp>
#include <jln/mp/detail/sequence.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int n>
    struct sort_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Sorts the elements of a \sequence according to an ordering relation.
  /// Sorting is stable.
  /// \post \c is_sorted<result...>
  /// \treturn \sequence
  template<class Cmp = less<>, class C = listify>
  struct sort
  {
    template<class... xs>
    using f = typename detail::_unpack<
      C,
      typename detail::sort_impl<sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(Cmp), xs...>
    >::type;
  };

  template<class Cmp = less<>, class C = listify>
  using stable_sort = sort<Cmp, C>;

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = listify>
    using sort = unpack<L, mp::sort<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = listify>
    using stable_sort = unpack<L, mp::sort<Cmp, C>>;
  }

  /// \cond
  template<class Cmp>
  struct sort<Cmp, listify>
  {
    template<class... xs>
    using f = typename detail::sort_impl<sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(Cmp), xs...>;
  };
  /// \endcond
}


#include <jln/mp/algorithm/merge.hpp>
#include <jln/mp/list/take_front.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/utility/always.hpp>

/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct mk_list2;

  template<>
  struct mk_list2<false>
    : listify
  {};

  template<>
  struct mk_list2<true>
  {
    template<class x, class y>
    using f = list<y, x>;
  };


  template<int n>
  struct sort_impl : sort_impl<
      n <= 8 ? 8
    : n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : 128
  >
  {};

  template<>
  struct sort_impl<0>
    : always<list<>>
  {};

  template<>
  struct sort_impl<1>
  {
    template<class Cmp, class x>
    using f = list<x>;
  };

  template<class Cmp, class x, class y>
  using sort_pair = typename mk_list2<bool(Cmp::template f<y, x>::value)>
    ::template f<x, y>;

  template<>
  struct sort_impl<2>
  {
    template<class Cmp, class x, class y>
    using f = sort_pair<Cmp, x, y>;
  };

  template<>
  struct sort_impl<3>
  {
    template<class Cmp, class x1, class x2, class x3>
    using f = typename merge_impl<
      list<>,
      sort_pair<Cmp, x1, x2>,
      list<x3>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<4>
  {
    template<class Cmp, class x1, class x2, class x3, class x4>
    using f = typename merge_impl<
      list<>,
      sort_pair<Cmp, x1, x2>,
      sort_pair<Cmp, x3, x4>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<5>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5>
    using f = typename merge_impl<
      list<>,
      sort_pair<Cmp, x1, x2>,
      typename sort_impl<3>::template f<Cmp, x3, x4, x5>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<6>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5,
             class x6>
    using f = typename merge_impl<
      list<>,
      typename sort_impl<3>::template f<Cmp, x1, x2, x3>,
      typename sort_impl<3>::template f<Cmp, x4, x5, x6>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<7>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5,
             class x6, class x7>
    using f = typename merge_impl<
      list<>,
      typename sort_impl<4>::template f<Cmp, x1, x2, x3, x4>,
      typename sort_impl<3>::template f<Cmp, x5, x6, x7>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<8>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5,
             class x6, class x7, class x8>
    using f = typename merge_impl<
      list<>,
      typename sort_impl<4>::template f<Cmp, x1, x2, x3, x4>,
      typename sort_impl<4>::template f<Cmp, x5, x6, x7, x8>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<16>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5,
             class x6, class x7, class x8, class... xs>
    using f = typename merge_impl<
      list<>,
      typename sort_impl<8>::template f<Cmp, x1, x2, x3, x4, x5, x6, x7, x8>,
      typename sort_impl<sizeof...(xs)>::template f<Cmp, xs...>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<32>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5,
             class x6, class x7, class x8, class x9, class x10, class x11,
             class x12, class x13, class x14, class x15, class x16, class... xs>
    using f = typename merge_impl<
      list<>,
      typename sort_impl<16>::template f<
        Cmp, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16>,
      typename sort_impl<sizeof...(xs)>::template f<Cmp, xs...>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<64>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5,
             class x6, class x7, class x8, class x9, class x10, class x11,
             class x12, class x13, class x14, class x15, class x16, class x17,
             class x18, class x19, class x20, class x21, class x22, class x23,
             class x24, class x25, class x26, class x27, class x28, class x29,
             class x30, class x31, class x32, class... xs>
    using f = typename merge_impl<
      list<>,
      typename sort_impl<32>::template f<
        Cmp, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15,
        x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29,
        x30, x31, x32>,
      typename sort_impl<sizeof...(xs)>::template f<Cmp, xs...>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<128>
  {
    template<class Cmp, JLN_MP_XS_32(class, JLN_MP_NIL, JLN_MP_COMMA), class... xs>
    using f = typename merge_impl<
      list<>,
      typename _unpack<sort<Cmp>, typename take_front_impl<(sizeof...(xs) + 32) / 2>
        ::template f<(sizeof...(xs) + 32) / 2, list<>,
          JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), xs...>>::type,
      typename drop_front_impl<(sizeof...(xs) + 32) / 2 - 32>
        ::template f<(sizeof...(xs) + 32) / 2 - 32, sort<Cmp>, xs...>,
      Cmp
    >::type;
  };
}
/// \endcond
