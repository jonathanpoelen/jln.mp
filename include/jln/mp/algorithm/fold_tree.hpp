#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/detail/enumerate.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<uint_>
    struct _fold_tree;

    template<uint_>
    struct _fold_balanced_tree;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Folds tree over a list using a binary predicate.
  /// recursively fold n/2 value to the left and the rest to the right.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<fold_tree::f<...xs[0..n/2]>, fold_tree::f<...xs[n/2..n]>>
  ///   \endcode
  /// \treturn \value
  /// \see fold_left, fold_right, fold_balanced_tree
  template<class F, class C = identity>
  struct fold_tree
  {
    template<class... xs>
    using f = typename detail::_fold_tree<
      detail::min(3, sizeof...(xs))
    >::template f<C, F, xs...>;
  };

  /// Folds tree over a list using a binary predicate.
  /// recursively fold (n+1)/2 value to the left and the rest to the right.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<fold_tree::f<...xs[0..(n+1)/2]>, fold_tree::f<...xs[n-(n+1)/2..n]>>
  ///   \endcode
  /// \treturn \value
  /// \see fold_left, fold_right, fold_tree
  template<class F, class C = identity>
  struct fold_balanced_tree
  {
    template<class... xs>
    using f = typename detail::_fold_balanced_tree<
      detail::min(3, sizeof...(xs))
    >::template f<C, F, xs...>;
  };

  namespace emp
  {
    template<class L, class F, class C = mp::identity>
    using fold_tree = unpack<L, mp::fold_tree<F, C>>;

    template<class L, class F, class C = mp::identity>
    using fold_balanced_tree = unpack<L, mp::fold_balanced_tree<F, C>>;
  }
}


#include "jln/mp/list/take_front.hpp"
#include "jln/mp/list/drop_front.hpp"

/// \cond
namespace jln::mp::detail
{
  // std::bit_ceil (c++20)
  constexpr uint_ bit_ceil(uint_ n)
  {
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
  }

  template<>
  struct _fold_tree<0>
  {
    template<class C, class F>
    using f = typename C::template f<>;
  };

  template<>
  struct _fold_tree<1>
  {
    template<class C, class F, class x>
    using f = typename C::template f<x>;
  };

  template<>
  struct _fold_tree<2>
  {
    template<class C, class F, class x, class y>
    using f = typename C::template f<typename F::template f<x, y>>;
  };

  template<class F, uint_>
  struct fold_tree_impl;

  template<class F>
  struct fold_tree_impl<F, 0>
  {
    template<class x>
    using f = x;
  };

  template<class F>
  struct fold_tree_impl<F, 1>
  {
    template<class x, class y>
    using f = typename F::template f<x, y>;
  };

  template<class F, uint_ n>
  struct fold_tree_impl
  {
    template<class... xs>
    using f = typename F::template f<
      JLN_MP_DCALL_XS(xs, take_front_c<n, fold_tree_impl<F, n/2>>, xs...),
      JLN_MP_DCALL_XS(xs, drop_front_c<n, fold_tree_impl<F, bit_ceil(sizeof...(xs)-n)/2>>, xs...)
    >;
  };

  template<>
  struct _fold_tree<3>
  {
    template<class C, class F, class... xs>
    using f = typename C::template f<
      typename fold_tree_impl<F, bit_ceil(sizeof...(xs))/2>::template f<xs...>
    >;
  };


  template<>
  struct _fold_balanced_tree<0>
  : _fold_tree<0>
  {};

  template<>
  struct _fold_balanced_tree<1>
  : _fold_tree<1>
  {};

  template<>
  struct _fold_balanced_tree<2>
  : _fold_tree<2>
  {};

  template<class F, uint_>
  struct fold_balanced_tree_impl;

  template<class F>
  struct fold_balanced_tree_impl<F, 1>
  {
    template<class x>
    using f = x;
  };

  template<class F>
  struct fold_balanced_tree_impl<F, 2>
  {
    template<class x, class y>
    using f = typename F::template f<x, y>;
  };

  template<class F, uint_ n>
  struct fold_balanced_tree_impl
  {
    template<class... xs>
    using f = typename F::template f<
      JLN_MP_DCALL_XS(xs, take_front_c<(n+1)/2, fold_balanced_tree_impl<F, (n+1)/2>>, xs...),
      JLN_MP_DCALL_XS(xs, drop_front_c<(n+1)/2, fold_balanced_tree_impl<F, n-(n+1)/2>>, xs...)
    >;
  };

  template<>
  struct _fold_balanced_tree<3>
  {
    template<class C, class F, class... xs>
    using f = typename C::template f<
      typename fold_balanced_tree_impl<F, sizeof...(xs)>::template f<xs...>
    >;
  };
}
/// \endcond
