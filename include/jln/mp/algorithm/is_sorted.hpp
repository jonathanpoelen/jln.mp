// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/operators.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_>
    struct is_sorted_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks whether a \sequence is sorted.
  /// \treturn \bool
  template<class Cmp = less<>, class C = identity>
  struct is_sorted
  {
    template<class... xs>
    using f = typename detail::is_sorted_impl<sizeof...(xs) < 3 ? sizeof...(xs) : 3>
      ::template f<C, Cmp, xs...>;
  };

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using is_sorted = unpack<L, mp::is_sorted<Cmp, C>>;
  }
}

#include <jln/mp/algorithm/pairwise.hpp>
#include <jln/mp/algorithm/drop_until_xs.hpp>

/// \cond
namespace jln::mp::detail
{
  template<>
  struct is_sorted_impl<0>
  {
    template<class C, class Cmp, class...>
    using f = JLN_MP_CALL_TRACE(C, true_);
  };

  template<>
  struct is_sorted_impl<1> : is_sorted_impl<0>
  {};

  template<>
  struct is_sorted_impl<2>
  {
    template<class C, class Cmp, class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_RAW_EXPR_TO_BOOL(Cmp::template f<x, y>::value)>);
  };

  template<class F>
  struct bind_and_flip_2
  {
    template<class x, class y, class... xs>
    using f = typename F::template f<y, x>;
  };

  template<>
  struct is_sorted_impl<3>
  {
    template<class C, class Cmp, class... xs>
    using f = JLN_MP_CALL_TRACE(C, typename is_drop_while_continue<
      detail::drop_until_xs_call<
        sizeof...(xs)-1,
        bind_and_flip_2<JLN_MP_TRACE_F(Cmp)>, xs...
      >
    >::type);
  };
}
/// \endcond
