// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/detail/expr_to_bool.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, bool>
    struct _powerset;
  }
  /// \endcond

  /// \ingroup group

  /// Computes the powerset of a \sequence.
  /// \semantics
  ///   \code
  ///   powerset<>::f<a, b, c> == list<
  ///     list<>,
  ///     list<a>, list<b>, list<a, b>, list<c>,
  ///     list<a, c>, list<b, c>,
  ///     list<a, b, c>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  template<class C = listify>
  struct powerset
  {
    template<class... xs>
    using f = typename detail::_powerset<C, JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs))>
      ::type::template f<list<list<>>, xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using powerset = typename detail::_unpack<mp::powerset<C>, L>::type;
  }
}


#include <jln/mp/algorithm/fold_right.hpp>
#include <jln/mp/list/clear.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/list/join.hpp>
#include <jln/mp/utility/always.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class, class>
  struct _power;

  template<class... xs, class y>
  struct _power<list<xs...>, y>
  {
    using type = list<list<xs...>, list<y, xs...>>;
  };

  template<class, class>
  struct powerset_impl;

  template<class... seqs, class y>
  struct powerset_impl<y, list<seqs...>>
  {
    using type = join<>::f<typename _power<seqs, y>::type...>;
  };

  template<class x, class y>
  using powerset_impl_t = typename powerset_impl<x, y>::type;

  template<class C>
  struct _powerset<C, false>
  {
    using type = fold_right<JLN_MP_CF_WRAP(powerset_impl), unpack<C>>;
  };

  template<>
  struct _powerset<listify, false>
  {
    using type = fold_right<JLN_MP_CF_WRAP(powerset_impl)>;
  };

  template<class C>
  struct _powerset<C, true>
  {
    using type = clear<C>;
  };
}
/// \endcond
