// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/utility/is.hpp>
#include <jln/mp/algorithm/transform.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class Pred, class Replacement>
    struct substitute_if;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Replaces every occurrence that satisfy a predicate by some \value.
  /// \treturn \sequence
  template<class Pred, class T, class C = listify>
  using replace_if = transform<detail::substitute_if<Pred, T>, C>;

  /// Replaces every occurrence of a \value by another \value.
  /// \treturn \sequence
  template<class T, class U, class C = listify>
  using replace = replace_if<is<T>, U, C>;

  namespace emp
  {
    template<class L, class T, class U, class C = mp::listify>
    using replace = typename detail::_unpack<mp::replace<T, U, C>, L>::type;

    template<class L, class Pred, class T, class C = mp::listify>
    using replace_if = typename detail::_unpack<mp::replace_if<Pred, T, C>, L>::type;
  }
}

#include <jln/mp/utility/conditional.hpp>
#include <jln/mp/functional/continuation.hpp>
#include <jln/mp/utility/is_not.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Pred, class Replacement>
  struct substitute_if
  {
    template<class x>
    using f = JLN_MP_CONDITIONAL_C_T(
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_TRACE_F(Pred)::template f<x>::value),
      x, Replacement
    );
  };

  template<class T, class Replacement>
  struct substitute_if<is<T>, Replacement>
  {
    template<class x>
    using f = JLN_MP_CONDITIONAL_C_T(JLN_MP_IS_SAME(T, x), Replacement, x);
  };

  template<class T, class Replacement>
  struct substitute_if<is_not<T>, Replacement>
  {
    template<class x>
    using f = JLN_MP_CONDITIONAL_C_T(JLN_MP_IS_SAME(T, x), x, Replacement);
  };

#if ! JLN_MP_DEBUG
  template<template<class...> class Pred, class Replacement>
  struct substitute_if<cfe<Pred>, Replacement>
  {
    template<class x>
    using f = JLN_MP_CONDITIONAL_C_T(
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred<x>::value),
      x, Replacement
    );
  };

  template<template<class...> class Pred, class Replacement>
  struct substitute_if<cfl<Pred>, Replacement>
  {
    template<class x>
    using f = JLN_MP_CONDITIONAL_C_T(
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred<x>::type::value),
      x, Replacement
    );
  };
#endif
}
/// \endcond
