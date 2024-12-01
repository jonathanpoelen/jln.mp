// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/split_before.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool... bs>
    struct mk_group_indices;

    template<bool>
    struct group_impl;
  }
  /// \endcond

  /// \ingroup group

  /// Groups adjacent elements that respect a predicate.
  /// \semantics
  ///   \code
  ///   group_by<same<>>::f<void, void, int, void>
  ///   == list<
  ///     list<void, void>,
  ///     list<int>,
  ///     list<void>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  template<class Cmp, class F = listify, class C = listify>
  struct group_by_with
  {
    template<class... xs>
    using f = typename detail::group_impl<JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs))>
      ::template f<JLN_MP_TRACE_F(Cmp), xs...>
      ::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };

  template<class F = listify, class C = listify>
  using group_with = group_by_with<same<>, F, C>;

  template<class Cmp, class C = listify>
  using group_by = group_by_with<Cmp, listify, C>;

  template<class C = listify>
  using group = group_by_with<same<>, listify, C>;

  namespace emp
  {
    template<class L, class Cmp, class F = listify, class C = listify>
    using group_by_with = typename detail::_unpack<mp::group_by_with<Cmp, F, C>, L>::type;

    template<class L, class F = listify, class C = listify>
    using group_with = typename detail::_unpack<mp::group_by_with<mp::same<>, F, C>, L>::type;

    template<class L, class Cmp, class C = listify>
    using group_by = typename detail::_unpack<mp::group_by_with<Cmp, listify, C>, L>::type;

    template<class L, class C = listify>
    using group = typename detail::_unpack<mp::group_by_with<mp::same<>, listify, C>, L>::type;
  }
}


#include <jln/mp/list/take_front.hpp>
#include <jln/mp/functional/try.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Cmp, class x, class ys, class... xs>
  struct mk_pairs_indices;

  template<class Cmp, class x, class... ys, class... xs>
  struct mk_pairs_indices<Cmp, x, list<ys...>, xs...>
    : array_int2_index_dispatcher<
      mk_split_before_indices<
        false,
        JLN_MP_RAW_EXPR_TO_BOOL_NOT(Cmp::template f<ys, xs>::value)...
      >
    >
  {};

  template<class x, class... ys, class... xs>
  struct mk_pairs_indices<same<>, x, list<ys...>, xs...>
    : array_int2_index_dispatcher<
      mk_split_before_indices<
        false,
        JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_IS_SAME(ys, xs))...
      >
    >
  {};

  template<class... ys>
  struct smp_mk_pairs_indices
  {
    template<class Cmp, class x, class... xs>
    using f = array_int2_index_dispatcher<
      mk_split_before_indices<
        false,
        JLN_MP_RAW_EXPR_TO_BOOL_NOT(Cmp::template f<ys, xs>::value)...
      >
    >;
  };

  template<class Cmp, class TC, class FC, class x, class... ys, class... xs>
  struct mk_pairs_indices<try_<Cmp, TC, FC>, x, list<ys...>, xs...>
    : try_<smp_mk_pairs_indices<ys...>>
    ::template f<try_<Cmp, TC, FC>, x, xs...>
  {};

  // needed when JLN_MP_ENABLE_DEBUG is enabled
  template<class Cmp, class x, class... ys, class... xs>
  struct mk_pairs_indices<memoize<Cmp>, x, list<ys...>, xs...>
    : try_<smp_mk_pairs_indices<ys...>>
    ::template f<memoize<Cmp>, x, xs...>
  {};

  template<>
  struct group_impl<false>
  {
    template<class Cmp, class x, class... xs>
    using f = mk_pairs_indices<
      JLN_MP_TRACE_F(Cmp),
      x,
      typename take_front_impl<sizeof...(xs)>
        ::template f<sizeof...(xs), list, x, xs...>,
      xs...
    >;
  };

  template<>
  struct group_impl<true>
  {
    template<class Cmp, class... xs>
    using f = call_trace_c0_arg;
  };
}
/// \endcond
