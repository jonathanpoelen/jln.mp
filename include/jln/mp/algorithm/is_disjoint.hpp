// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/same.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<uint_>
    struct is_disjoint_select;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks whether \value in `seqs[0]` are disjoint from the \value in `seqs[1:]`.
  /// Returns `mp::true_` when `sizeof...(seqs) < 2`
  /// \treturn \bool
  /// \see is_disjoint, is_subset, is_subset_with
  template<class Cmp = same<>, class C = identity>
  struct is_disjoint_with
  {
    template<class... seqs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::is_disjoint_select<sizeof...(seqs) < 3 ? sizeof...(seqs) : 3>
      ::template f<JLN_MP_TRACE_F(Cmp), seqs...>);
  };

  /// Checks whether \value in `seqs[0]` are disjoint from the \value in `seqs[1:]`.
  /// Returns `mp::true_` when `sizeof...(seqs) < 2`
  /// \treturn \bool
  /// \see is_disjoint_with, is_subset, is_subset_with
  template<class C = identity>
  using is_disjoint = is_disjoint_with<same<>, C>;

  namespace emp
  {
#ifdef JLN_MP_DOXYGENATING
    template<class L1, class L2, class C = mp::identity>
    using is_disjoint = typename is_disjoint<C>::template f<L1, L2>;

    template<class L1, class L2, class Cmp = same<>, class C = mp::identity>
    using is_disjoint_with = typename is_disjoint_with<Cmp, C>::template f<L1, L2>;
#endif
  }

  /// \cond
  template<class Cmp>
  struct is_disjoint_with<Cmp, identity>
  {
    template<class... seqs>
    using f = typename detail::is_disjoint_select<sizeof...(seqs) < 3 ? sizeof...(seqs) : 3>
      ::template f<JLN_MP_TRACE_F(Cmp), seqs...>;
  };
  /// \endcond
}


/// \cond
#include <jln/mp/algorithm/drop_until.hpp>
#include <jln/mp/functional/lift.hpp>
#include <jln/mp/list/push_back.hpp>

namespace jln::mp::detail
{
  template<class Pred>
  struct is_disjoint_impl
  {
    template<class... xs>
    using f = typename is_drop_while_continue<
      typename _drop_while<sizeof...(xs)>::template f<0, Pred, xs...>
    >::type;
  };

  template<class Cmp, class... xs>
  struct is_disjoint_of
  {
    template<class x>
    using f = typename is_drop_while_continue<
      typename _drop_until<sizeof...(xs)>::template f<0, push_back<x, Cmp>, xs...>
    >::type;
  };

  template<>
  struct is_disjoint_select<0>
  {
    template<class Cmp, class... xs>
    using f = true_;
  };

  template<>
  struct is_disjoint_select<1> : is_disjoint_select<0>
  {};

  template<class Cmp, class seq0>
  using to_is_disjoint_impl = is_disjoint_impl<
    typename _unpack<lift<is_disjoint_of>, seq0, Cmp>::type
  >;

  template<>
  struct is_disjoint_select<2>
  {
    template<class Cmp, class seq0, class seq1>
    using f = typename _unpack<to_is_disjoint_impl<Cmp, seq0>, seq1>::type;
  };

  template<>
  struct is_disjoint_select<3>
  {
    template<class Cmp, class seq0, class... seqs>
    using f = typename is_drop_while_continue<
      typename _drop_while<sizeof...(seqs)>::template f<
        0,
        unpack<to_is_disjoint_impl<Cmp, seq0>>,
        seqs...
      >
    >::type;
  };
}

#ifndef JLN_MP_DOXYGENATING
namespace jln::mp::emp
{
  template<class L1, class L2, class C = mp::identity>
  using is_disjoint = typename C::template f<
    typename detail::is_disjoint_select<2>::f<mp::same<>, L1, L2>
  >;

  template<class L1, class L2, class Cmp = mp::same<>, class C = mp::identity>
  using is_disjoint_with = typename C::template f<
    typename detail::is_disjoint_select<2>::f<Cmp, L1, L2>
  >;
}
#endif
/// \endcond
