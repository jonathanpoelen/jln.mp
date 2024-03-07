// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/is_disjoint.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<uint_>
    struct _is_subset;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks whether \value in `seqs[0]` are subset from the \value in `seqs[1:]`.
  /// Returns `mp::true_` when `sizeof...(seqs) < 2`
  /// \treturn \bool
  /// \see is_subset
  template<class Cmp = same<>, class C = identity>
  struct is_subset_with
  {
    template<class... seqs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::_is_subset<sizeof...(seqs) < 3 ? sizeof...(seqs) : 3>
      ::template f<JLN_MP_TRACE_F(Cmp), seqs...>
    );
  };

  /// Checks whether \value in `seqs[0]` are subset from the \value in `seqs[1:]`.
  /// Returns `mp::true_` when `sizeof...(seqs) < 2`
  /// \treturn \bool
  /// \see is_subset_with
  template<class C = identity>
  using is_subset = is_subset_with<same<>, C>;

#ifdef JLN_MP_DOXYGENATING
  namespace emp
  {
    template<class L1, class L2, class C = mp::identity>
    using is_subset = typename is_subset<C>::template f<L1, L2>;

    template<class L1, class L2, class Cmp = mp::same<>, class C = mp::identity>
    using is_subset_with = typename is_subset_with<Cmp, C>::template f<L1, L2>;

    template<class L1, class L2>
    constexpr bool is_subset = is_subset<>::template f<L1, L2>::value;

    template<class L1, class L2, class Cmp = mp::same<>>
    constexpr bool is_subset_with = is_subset_with<Cmp>::template f<L1, L2>::value;
  }
#endif

  /// \cond
  template<class Cmp>
  struct is_subset_with<Cmp, identity>
  {
    template<class... seqs>
    using f = typename detail::_is_subset<sizeof...(seqs) < 3 ? sizeof...(seqs) : 3>
      ::template f<JLN_MP_TRACE_F(Cmp), seqs...>;
  };
  /// \endcond
}


/// \cond
namespace jln::mp::detail
{
  template<class Cmp, class... xs>
  struct _is_subset_of
  {
    template<class x>
    using f = number<!is_drop_while_continue<
      typename _drop_until<sizeof...(xs)>::template f<0, push_back<x, Cmp>, xs...>
    >::type::value>;
  };

  template<>
  struct _is_subset<0> : is_disjoint_select<0>
  {};

  template<>
  struct _is_subset<1> : is_disjoint_select<0>
  {};

  template<class Cmp, class seq0>
  using to_is_subset_impl = is_disjoint_impl<
    typename _unpack<lift<_is_subset_of>, seq0, Cmp>::type
  >;

  template<>
  struct _is_subset<2>
  {
    template<class Cmp, class seq0, class seq1>
    using f = typename _unpack<to_is_subset_impl<Cmp, seq0>, seq1>::type;
  };

  template<>
  struct _is_subset<3>
  {
    template<class Cmp, class seq0, class... seqs>
    using f = typename detail::is_drop_while_continue<
      typename _drop_while<sizeof...(seqs)>::template f<
        0,
        unpack<to_is_subset_impl<Cmp, seq0>>,
        seqs...
    >>::type;
  };
}

#ifndef JLN_MP_DOXYGENATING
namespace jln::mp::emp
{
  template<class L1, class L2, class C = mp::identity>
  using is_subset = typename C::template f<
    typename detail::_is_subset<2>::f<mp::same<>, L1, L2>
  >;

  template<class L1, class L2, class Cmp = mp::same<>, class C = mp::identity>
  using is_subset_with = typename C::template f<
    typename detail::_is_subset<2>::f<Cmp, L1, L2>
  >;

  template<class L1, class L2>
  constexpr bool is_subset_v = detail::_is_subset<2>::f<mp::same<>, L1, L2>::value;

  template<class L1, class L2, class Cmp = mp::same<>, class C = mp::identity>
  constexpr bool is_subset_with_v = detail::_is_subset<2>::f<Cmp, L1, L2>::value;
}
#endif
/// \endcond
