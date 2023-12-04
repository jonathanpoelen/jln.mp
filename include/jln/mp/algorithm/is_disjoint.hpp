// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/lift.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/detail/sequence.hpp>

#include <type_traits>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<uint_>
    struct _is_disjoint;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks whether \value in `seqs[0]` are disjoint from the \value in `seqs[1:]`.
  /// Returns `mp::true_` when `sizeof...(seqs) < 2`
  /// \treturn \bool
  /// \see is_disjoint, is_subset, is_subset_with
  template<class Equal = lift<std::is_same>, class C = identity>
  struct is_disjoint_with
  {
    template<class... seqs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::_is_disjoint<sizeof...(seqs) < 3 ? sizeof...(seqs) : 3>
      ::template f<JLN_MP_TRACE_F(Equal), seqs...>);
  };

  /// Checks whether \value in `seqs[0]` are disjoint from the \value in `seqs[1:]`.
  /// Returns `mp::true_` when `sizeof...(seqs) < 2`
  /// \treturn \bool
  /// \see is_disjoint_with, is_subset, is_subset_with
  template<class C = identity>
  using is_disjoint = is_disjoint_with<lift<std::is_same>, C>;

  namespace emp
  {
#ifdef JLN_MP_DOXYGENATING
    template<class L1, class L2, class C = mp::identity>
    using is_disjoint = typename is_disjoint<C>::template f<L1, L2>;

    template<class L1, class L2, class Equal = lift<std::is_same>, class C = mp::identity>
    using is_disjoint_with = typename is_disjoint_with<Equal, C>::template f<L1, L2>;
#endif
  }

  /// \cond
  template<class Equal>
  struct is_disjoint_with<Equal, identity>
  {
    template<class... seqs>
    using f = typename detail::_is_disjoint<sizeof...(seqs) < 3 ? sizeof...(seqs) : 3>
      ::template f<JLN_MP_TRACE_F(Equal), seqs...>;
  };
  /// \endcond
}


#include <jln/mp/algorithm/drop_until.hpp>
#include <jln/mp/list/push_back.hpp>

/// \cond
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

  template<class Equal, class... xs>
  struct _is_disjoint_of
  {
    template<class x>
    using f = typename is_drop_while_continue<
      typename _drop_until<sizeof...(xs)>::template f<0, push_back<x, Equal>, xs...>
    >::type;
  };

  template<>
  struct _is_disjoint<0>
  {
    template<class Equal, class... xs>
    using f = true_;
  };

  template<>
  struct _is_disjoint<1> : _is_disjoint<0>
  {};

  template<class Equal, class seq0>
  using to_is_disjoint_impl = is_disjoint_impl<
    typename _unpack<lift<_is_disjoint_of>, seq0, Equal>::type
  >;

  template<>
  struct _is_disjoint<2>
  {
    template<class Equal, class seq0, class seq1>
    using f = typename _unpack<to_is_disjoint_impl<Equal, seq0>, seq1>::type;
  };

  template<>
  struct _is_disjoint<3>
  {
    template<class Equal, class seq0, class... seqs>
    using f = typename is_drop_while_continue<
      typename _drop_while<sizeof...(seqs)>::template f<
        0,
        unpack<to_is_disjoint_impl<Equal, seq0>>,
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
    typename detail::_is_disjoint<2>::f<mp::lift<std::is_same>, L1, L2>
  >;

  template<class L1, class L2, class Equal = lift<std::is_same>, class C = mp::identity>
  using is_disjoint_with = typename C::template f<
    typename detail::_is_disjoint<2>::f<Equal, L1, L2>
  >;
}
#endif
/// \endcond
