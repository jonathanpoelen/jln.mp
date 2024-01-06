// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/utility/is.hpp>
#include <jln/mp/algorithm/transform.hpp>

namespace jln::mp
{
  /// \endcond
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
    using replace = unpack<L, mp::replace<T, U, C>>;

    template<class L, class Pred, class T, class C = mp::listify>
    using replace_if = unpack<L, mp::replace_if<Pred, T, C>>;
  }
}

#include <jln/mp/utility/conditional.hpp>
#include <jln/mp/functional/lift.hpp>
#include <jln/mp/utility/is_not.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Pred, class Replacement>
  struct substitute_if
  {
    template<class x>
    using f = typename conditional_c<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_TRACE_F(Pred)::template f<x>::value)
    >::template f<x, Replacement>;
  };

  template<class T, class Replacement>
  struct substitute_if<is<T>, Replacement>
  {
    template<class x>
    using f = typename conditional_c<std::is_same<T, x>::value>
      ::template f<Replacement, x>;
  };

  template<class T, class Replacement>
  struct substitute_if<is_not<T>, Replacement>
  {
    template<class x>
    using f = typename conditional_c<std::is_same<T, x>::value>
      ::template f<x, Replacement>;
  };

#if ! JLN_MP_ENABLE_DEBUG
  template<template<class...> class Pred, class Replacement>
  struct substitute_if<lift<Pred>, Replacement>
  {
    template<class x>
    using f = typename conditional_c<JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred<x>::value)>
      ::template f<x, Replacement>;
  };

  template<template<class...> class Pred, class Replacement>
  struct substitute_if<lift_t<Pred>, Replacement>
  {
    template<class x>
    using f = typename conditional_c<JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred<x>::type::value)>
      ::template f<x, Replacement>;
  };
#endif
}
/// \endcond
