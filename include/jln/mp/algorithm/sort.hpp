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
    using sort = typename detail::_unpack<mp::sort<Cmp, C>, L>::type;

    template<class L, class Cmp = mp::less<>, class C = listify>
    using stable_sort = typename detail::_unpack<mp::sort<Cmp, C>, L>::type;
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
  struct mk_list2<true>
    : listify
  {};

  template<>
  struct mk_list2<false>
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


#if JLN_MP_HAS_MEMOIZED_ALIAS
  template<class Cmp, class x, class y>
  using sort_pair = typename mk_list2<JLN_MP_RAW_EXPR_TO_BOOL_NOT(Cmp::template f<y, x>::value)>
      ::template f<x, y>;
  #define JLN_MP_SORT2(...) sort_pair<__VA_ARGS__>
#else
  template<class Cmp, class x, class y>
  struct sort_pair_impl
  {
    using type = typename mk_list2<JLN_MP_RAW_EXPR_TO_BOOL_NOT(Cmp::template f<y, x>::value)>
      ::template f<x, y>;
  };
  #define JLN_MP_SORT2(...) typename sort_pair_impl<__VA_ARGS__>::type
#endif

  template<>
  struct sort_impl<2>
  {
    template<class Cmp, class x, class y>
    using f = JLN_MP_SORT2(Cmp, x, y);
  };


  template<class Cmp, class x, class y, class z>
  constexpr auto sort3()
  {
    if constexpr (Cmp::template f<y, x>::value)
    {
      if constexpr (Cmp::template f<z, y>::value)
      {
        return list<z,y,x>{};
      }
      else if constexpr (Cmp::template f<z, x>::value)
      {
        return list<y,z,x>{};
      }
      else
      {
        return list<y,x,z>{};
      }
    }
    else if constexpr (Cmp::template f<z, y>::value)
    {
      if constexpr (Cmp::template f<z, x>::value)
      {
        if constexpr (Cmp::template f<x, y>::value) // for stable sort
        {
          return list<z,x,y>{};
        }
        else
        {
          return list<z,y,x>{};
        }
      }
      else
      {
        return list<x,z,y>{};
      }
    }
    else
    {
      return list<x,y,z>{};
    }
  }

  template<>
  struct sort_impl<3>
  {
    template<class Cmp, class x1, class x2, class x3>
    using f = decltype(sort3<Cmp, x1, x2, x3>());
  };

#if ! JLN_MP_GCC
  template<class>
  struct get_l3;

  template<class x, class y, class z>
  struct get_l3<list<x,y,z>>
  {
    using x1 = x;
    using x2 = y;
    using x3 = z;
  };

  template<class Cmp, class a1, class a2, class a3, class x4>
  constexpr auto sort4()
  {
    using l = get_l3<decltype(sort3<Cmp,a1,a2,a3>())>;
    using x1 = typename l::x1;
    using x2 = typename l::x2;
    using x3 = typename l::x3;

    if constexpr (Cmp::template f<x4, x2>::value)
    {
      if constexpr (Cmp::template f<x4, x1>::value)
      {
        return list<x4,x1,x2,x3>{};
      }
      else
      {
        return list<x1,x4,x2,x3>{};
      }
    }
    else if constexpr (Cmp::template f<x4, x3>::value)
    {
      return list<x1,x2,x4,x3>{};
    }
    else
    {
      return list<x1,x2,x3,x4>{};
    }
  }

  template<>
  struct sort_impl<4>
  {
    template<class Cmp, class x1, class x2, class x3, class x4>
    using f = decltype(sort4<Cmp, x1, x2, x3, x4>());
  };
  #define JLN_MP_SORT4(...) decltype(sort4<__VA_ARGS__>())
#else // if JLN_MP_GCC
  template<>
  struct sort_impl<4>
  {
    template<class Cmp, class x1, class x2, class x3, class x4>
    using f = typename merge_impl<
      list<>,
      JLN_MP_SORT2(Cmp, x1, x2),
      JLN_MP_SORT2(Cmp, x3, x4),
      Cmp
    >::type;
  };
  #define JLN_MP_SORT4(...) typename sort_impl<4>::template f<__VA_ARGS__>
#endif



  template<>
  struct sort_impl<5>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5>
    using f = typename merge_impl<
      list<>,
      JLN_MP_SORT2(Cmp, x1, x2),
      decltype(sort3<Cmp, x3, x4, x5>()),
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
      decltype(sort3<Cmp, x1, x2, x3>()),
      decltype(sort3<Cmp, x4, x5, x6>()),
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
      JLN_MP_SORT4(Cmp, x1, x2, x3, x4),
      decltype(sort3<Cmp, x5, x6, x7>()),
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
      JLN_MP_SORT4(Cmp, x1, x2, x3, x4),
      JLN_MP_SORT4(Cmp, x5, x6, x7, x8),
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
      typename take_front_impl<(sizeof...(xs) + 32) / 2>
        ::template f<(sizeof...(xs) + 32) / 2, sort<Cmp>::template f,
          JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), xs...>,
      typename drop_front_impl<(sizeof...(xs) + 32) / 2 - 32>
        ::template f<(sizeof...(xs) + 32) / 2 - 32, sort<Cmp>::template f, xs...>,
      Cmp
    >::type;
  };

#undef JLN_MP_SORT2
#undef JLN_MP_SORT4
}
/// \endcond
