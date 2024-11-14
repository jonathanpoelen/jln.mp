// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/if.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/detail/sequence.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct fold_tree_select;

    template<int>
    struct fold_balanced_tree_select;
  }
  /// \endcond

  /// \ingroup reduce

  /// Folds tree over a list using a binary predicate.
  /// recursively fold n/2 value to the left and the rest to the right.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<fold_tree::f<...xs[0..n/2]>, fold_tree::f<...xs[n/2..n]>>
  ///   \endcode
  /// \treturn \value
  /// \see fold, fold_right, fold_balanced_tree
  template<class F, class C = identity>
  struct fold_tree
  {
    template<class... xs>
    using f = typename detail::fold_tree_select<
      sizeof...(xs) < 3 ? sizeof...(xs) : 3
    >::template f<C, JLN_MP_TRACE_F(F), xs...>;
  };

  /// Folds tree over a list using a binary predicate.
  /// Like \c fold_tree<>, but uses \c EmptyC when \c xs is empty.
  /// \treturn \value
  /// \see fold, fold_right, fold_tree, reverse_fold, fold_balanced_tree
  template<class F, class EmptyC, class C = identity>
  using fold_tree_or_else = if_<size<>, fold_tree<F, C>, EmptyC>;

  template<class F, class FallbackValue, class C = identity>
  using fold_tree_or = if_<size<>, fold_tree<F, C>, always<FallbackValue>>;

  /// Folds tree over a list using a binary predicate.
  /// recursively fold (n+1)/2 value to the left and the rest to the right.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<fold_tree::f<...xs[0..(n+1)/2]>, fold_tree::f<...xs[n-(n+1)/2..n]>>
  ///   \endcode
  /// \treturn \value
  /// \see fold, fold_right, fold_tree
  template<class F, class C = identity>
  struct fold_balanced_tree
  {
    template<class... xs>
    using f = typename detail::fold_balanced_tree_select<
      sizeof...(xs) < 3 ? sizeof...(xs) : 3
    >::template f<C, JLN_MP_TRACE_F(F), xs...>;
  };

  /// Folds tree over a list using a binary predicate.
  /// Like \c fold_balanced_tree<>, but uses \c EmptyC when \c xs is empty.
  /// \treturn \value
  /// \see fold, fold_right, fold_tree, reverse_fold, fold_balanced_tree
  template<class F, class EmptyC, class C = identity>
  using fold_balanced_tree_or_else = if_<size<>, fold_balanced_tree<F, C>, EmptyC>;

  template<class F, class FallbackValue, class C = identity>
  using fold_balanced_tree_or = if_<size<>, fold_balanced_tree<F, C>, always<FallbackValue>>;

  namespace emp
  {
    template<class L, class F, class C = mp::identity>
    using fold_tree = typename detail::_unpack<mp::fold_tree<F, C>, L>::type;

    template<class L, class F, class FallbackValue, class C = mp::identity>
    using fold_tree_or = typename detail::_unpack<
      mp::fold_tree_or_else<F, always<FallbackValue>, C>, L>::type;

    template<class L, class F, class EmptyC = F, class C = mp::identity>
    using fold_tree_or_else = typename detail::_unpack<mp::fold_tree_or_else<F, EmptyC, C>, L>::type;

    template<class L, class F, class C = mp::identity>
    using fold_balanced_tree = typename detail::_unpack<mp::fold_balanced_tree<F, C>, L>::type;

    template<class L, class F, class FallbackValue, class C = mp::identity>
    using fold_balanced_tree_or = typename detail::_unpack<
      mp::fold_balanced_tree_or_else<F, always<FallbackValue>, C>, L>::type;

    template<class L, class F, class EmptyC = F, class C = mp::identity>
    using fold_balanced_tree_or_else = typename detail::_unpack<
      mp::fold_balanced_tree_or_else<F, EmptyC, C>, L>::type;
  }
}


#include <jln/mp/algorithm/split_at.hpp>
#include <jln/mp/list/take_front.hpp>
#include <jln/mp/list/drop_front.hpp>

namespace jln::mp::detail
{
  constexpr unsigned bit_ceil(unsigned n)
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
  struct fold_tree_select<0> : call_trace_c0_arg
  {};

  template<>
  struct fold_tree_select<1>
  {
    template<class C, class F, class x>
    using f = JLN_MP_CALL_TRACE(C, x);
  };

  template<>
  struct fold_tree_select<2>
  {
    template<class C, class F, class x, class y>
    using f = JLN_MP_CALL_TRACE(C, typename F::template f<x, y>);
  };

  template<class F, unsigned>
  struct fold_tree_impl;

  template<class F>
  struct fold_tree_impl<F, 0> : identity
  {};

  template<class F>
  struct fold_tree_impl<F, 1>
  {
    template<class x, class y>
    using f = typename F::template f<x, y>;
  };

  template<class F>
  struct fold_tree_impl<F, 2>
  {
    template<class x, class y, class... xs>
    using f = typename F::template f<
      typename F::template f<x, y>,
      typename fold_tree_impl<F, sizeof...(xs)-1>::template f<xs...>
    >;
  };

  template<class F, unsigned n>
  struct fold_tree_impl
  {
#if JLN_MP_MEMOIZED_ALIAS
    template<class... xs>
    using f = typename F::template f<
      typename take_front_c<n, fold_tree_impl<F, n/2>>
        ::template f<xs...>,
      typename drop_front_c<n, fold_tree_impl<F, bit_ceil(sizeof...(xs)-n)/2>>
        ::template f<xs...>
    >;
#else
    template<class... xs>
    using f = typename detail::split_at_with_impl<
      F,
      fold_tree_impl<F, n/2>,
      fold_tree_impl<F, bit_ceil(sizeof...(xs)-n)/2>,
      typename detail::split_at_impl<(void(sizeof...(xs)), n)>
        ::template f<n, list<>, xs...>
    >::type;
#endif
  };

  template<>
  struct fold_tree_select<3>
  {
    template<class C, class F, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename fold_tree_impl<F, bit_ceil(sizeof...(xs))/2>::template f<xs...>
    );
  };


  template<>
  struct fold_balanced_tree_select<0> : call_trace_c0_arg
  {};

  template<>
  struct fold_balanced_tree_select<1> : fold_tree_select<1>
  {};

  template<>
  struct fold_balanced_tree_select<2> : fold_tree_select<2>
  {};

  template<class F, uint_>
  struct fold_balanced_tree_impl;

  template<class F>
  struct fold_balanced_tree_impl<F, 1> : identity
  {};

  template<class F>
  struct fold_balanced_tree_impl<F, 2> : fold_tree_impl<F, 1>
  {};

  template<class F>
  struct fold_balanced_tree_impl<F, 3> : fold_tree_impl<F, 2>
  {};

  template<class F, uint_ n>
  struct fold_balanced_tree_impl
  {
#if JLN_MP_MEMOIZED_ALIAS
    template<class... xs>
    using f = typename F::template f<
      typename take_front_c<(n+1)/2, fold_balanced_tree_impl<F, (n+1)/2>>
        ::template f<xs...>,
      typename drop_front_c<(sizeof...(xs) & 0) + (n+1)/2, fold_balanced_tree_impl<F, n-(n+1)/2>>
        ::template f<xs...>
    >;
#else
    template<class... xs>
    using f = typename detail::split_at_with_impl<
      F,
      fold_balanced_tree_impl<F, (n+1)/2>,
      fold_balanced_tree_impl<F, n-(n+1)/2>,
      typename detail::split_at_impl<(sizeof...(xs) & 0) + (n+1)/2>
        ::template f<(n+1)/2, list<>, xs...>
    >::type;
#endif
  };

  template<>
  struct fold_balanced_tree_select<3>
  {
    template<class C, class F, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename fold_balanced_tree_impl<F, sizeof...(xs)>::template f<xs...>
    );
  };
}
/// \endcond
