// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/operators.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_t>
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
    using is_sorted = typename detail::_unpack<mp::is_sorted<Cmp, C>, L>::type;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    constexpr bool is_sorted_v = detail::_unpack<mp::is_sorted<Cmp, C>, L>::type::value;
  }
}

#include <jln/mp/algorithm/none_of.hpp>
#include <jln/mp/algorithm/pairwise.hpp>

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

  template<class Cmp>
  struct cmp_w
  {
    template<class x, class y>
    struct f
    {
      using type = typename Cmp::template f<y, x>;
    };
  };

  struct type_t { template<class x> using f = typename x::type; };

  template<>
  struct is_sorted_impl<3>
  {
    template<class C, class Cmp, class... xs>
    using f = typename pairwise_with<cmp_w<Cmp>, none_of<type_t>>
      ::template f<xs...>;
  };
}
/// \endcond
