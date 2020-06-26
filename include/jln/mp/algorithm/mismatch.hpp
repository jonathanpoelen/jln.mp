#pragma once

#include "../number/operators.hpp"

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class, class>
    struct _mismatch;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Returns mismatching info of elements from two sequences.
  /// Uses \c C when a element mismatch and \c NC when one of
  /// the sequences equals the start of the other.
  /// \semantic
  ///   `NC::f<number<-1>, number<emp::size<seq1>>>` if \c seq1 == \c seq2.
  ///   `NC::f<number<i>, number<-1>>` if \c seq2 starts with \c seq1.
  ///   `NC::f<number<i>, number<1>>` if \c seq1 starts with \c seq2.
  ///   otherwise `C::f<number<i>, number<0>>`.
  /// \treturn pair or \number
  template<class Cmp = equal<>, class C = listify, class NC = C>
  struct mismatch
  {
    template<class seq1, class seq2>
    using f = typename detail::_mismatch<seq1, seq2>::template f<Cmp, C, NC>;
  };

  namespace emp
  {
    template<class seq1, class seq2, class Cmp = mp::equal<>, class C = mp::listify, class NC = C>
    using mismatch = call<mismatch<Cmp, C, NC>, seq1, seq2>;
  }
}


#include "../list/drop.hpp"
#include "../list/take.hpp"

namespace jln::mp::detail
{
  template<class Cmp, int n>
  struct _mismatch_tree;

  template<class Cmp>
  struct _mismatch_tree<Cmp, 1>
  {
    struct type
    {
      template<class x, class y>
      using f = number<call<Cmp, x, y>::value>;
    };
  };

  template<class Cmp>
  struct _mismatch_tree<Cmp, 2>
  {
    struct type
    {
      template<class x0, class x1, class y0, class y1>
      using f = number<
        !call<Cmp, x0, y0>::value ? 0
      : !call<Cmp, x1, y1>::value ? 1
      : 2
      >;
    };
  };

  template<class Cmp>
  struct _mismatch_tree<Cmp, 3>
  {
    struct type
    {
      template<class x0, class x1, class x2, class y0, class y1, class y2>
      using f = number<
        !call<Cmp, x0, y0>::value ? 0
      : !call<Cmp, x1, y1>::value ? 1
      : !call<Cmp, x2, y2>::value ? 2
      : 3
      >;
    };
  };

  template<class Cmp>
  struct _mismatch_tree<Cmp, 4>
  {
    struct type
    {
      template<class x0, class x1, class x2, class x3, class y0, class y1, class y2, class y3>
      using f = number<
        !call<Cmp, x0, y0>::value ? 0
      : !call<Cmp, x1, y1>::value ? 1
      : !call<Cmp, x2, y2>::value ? 2
      : !call<Cmp, x3, y3>::value ? 3
      : 4
      >;
    };
  };

  constexpr int_ _mismatch_size(int n)
  {
    // is pow 2
    if ((-n ^ n) <  -n) {
      return n/2;
    }

    if (n > 0xffff) {
      return 0x10000;
    }

    // std::bit_floor (c++20)
    int r = 1;

    if (n > 0xff) {
      r <<= 8;
      n >>= 8;
    }

    if (n > 0xf) {
      r <<= 4;
      n >>= 4;
    }

    if (n > 0b11) {
      r <<= 2;
      n >>= 2;
    }

    return (n > 0b1) ? (r << 1) : r;
  }

  template<class Cmp, int_ n, int_ size = _mismatch_size(n)>
  struct _mismatch_tree_next
  {
    template<class i, class = void>
    struct dispatch
    {
      template<class...>
      using f = i;
    };

    template<class v>
    struct dispatch<number<size>, v>
    {
      template<class... xs>
      using f = number<size + call<
        drop_c<size,
          rotate_c<n-size,
            drop_c<size,
              typename _mismatch_tree<Cmp, n-size>::type
            >
          >
        >,
        xs...
      >::value>;
    };

    template<class... xs>
    using f = typename dispatch<
      typename rotate_c<size,
        drop_c<n-size,
          rotate_c<size,
            drop_c<n-size,
              typename _mismatch_tree<Cmp, size>::type
            >
          >
        >
      >::template f<xs...>
    >::template f<xs...>;
  };

  template<class Cmp, int n>
  struct _mismatch_tree
  {
    using type = _mismatch_tree_next<Cmp, n>;
  };

  template<
    template<class...> class Txs, class... xs,
    template<class...> class Tys, class... ys>
  struct _mismatch<Txs<xs...>, Tys<ys...>>
  {
    template<class i, class n>
    struct apply_index
    {
      template<class C, class NC, class, class>
      using f = typename C::template f<i, number<0>>;
    };

    template<class n>
    struct apply_index<n, n>
    {
      template<class C, class NC, class i, class r>
      using f = typename NC::template f<i, r>;
    };

    template<bool, bool>
    struct impl
    {
      template<class Cmp, class C, class NC>
      using f = typename apply_index<
        typename _mismatch_tree<Cmp, sizeof...(xs)>::type
        ::template f<xs..., ys...>,
        number<sizeof...(xs)>
      >::template f<C, NC, number<-1>, number<sizeof...(xs)>>;
    };

    template<bool b>
    struct impl<true, b>
    {
      template<class Cmp, class C, class NC>
      using f = typename apply_index<
        typename take_c<
          sizeof...(xs) * 2,
          typename _mismatch_tree<Cmp, sizeof...(xs)>::type
        >::template f<xs..., ys...>,
        number<sizeof...(xs)>
      >::template f<C, NC, number<sizeof...(xs)>, number<-1>>;
    };

    template<bool b>
    struct impl<b, true>
    {
      template<class Cmp, class C, class NC>
      using f = typename apply_index<
        typename take_c<
          sizeof...(ys) * 2,
          typename _mismatch_tree<Cmp, sizeof...(ys)>::type
        >::template f<ys..., xs...>,
        number<sizeof...(ys)>
      >::template f<C, NC, number<sizeof...(ys)>, number<1>>;
    };

    template<class Cmp, class C, class NC>
    using f = typename impl<
      (sizeof...(xs) < sizeof...(ys)),
      (sizeof...(ys) < sizeof...(xs))
    >::template f<Cmp, C, NC>;
  };

  template<
    template<class...> class Txs,
    template<class...> class Tys, class... ys>
  struct _mismatch<Txs<>, Tys<ys...>>
  {
    template<class Cmp, class C, class NC>
    using f = typename NC::template f<number<0>, number<-1>>;
  };

  template<
    template<class...> class Txs, class... xs,
    template<class...> class Tys>
  struct _mismatch<Txs<xs...>, Tys<>>
  {
    template<class Cmp, class C, class NC>
    using f = typename NC::template f<number<0>, number<1>>;
  };

  template<template<class...> class Txs, template<class...> class Tys>
  struct _mismatch<Txs<>, Tys<>>
  {
    template<class Cmp, class C, class NC>
    using f = typename NC::template f<number<-1>, number<0>>;
  };
}
