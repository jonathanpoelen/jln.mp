// SPDX-FileCopyrightText: 2025 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/fold.hpp>
#include <jln/mp/algorithm/same.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class Cmp>
    struct set_cmp_push_back;

    template<class x, class F>
    struct unique_if_impl;
  }
  /// \endcond

  /// \ingroup filter

  /// Returns a list with duplicate elements removed.
  /// Only the first element found is kept.
  /// \treturn \sequence
  template<class Cmp = same<>, class C = listify>
  struct unique_if
  : detail::unique_if_impl<
      list<>,
      fold<
        unpack<detail::set_cmp_push_back<JLN_MP_TRACE_F(Cmp)>>,
        detail::optimize_useless_unpack_t<unpack<C>>
      >
    >
  {
#ifdef JLM_MP_DOXYGANATING
    template<class... xs>
    using f;
#endif
  };

  /// Returns a list with duplicate elements removed.
  /// \treturn \set
  template<class C = listify>
  using unique = unique_if<same<>, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using unique = typename detail::_unpack<unique<C>, L>::type;

    template<class L, class Cmp = mp::same<>, class C = mp::listify>
    using unique_if = typename detail::_unpack<unique_if<Cmp, C>, L>::type;
  }
}


#include <jln/mp/algorithm/none_of.hpp>
#include <jln/mp/utility/conditional.hpp>
#include <jln/mp/utility/inherit.hpp>
#include <jln/mp/utility/is_base_of.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/list/join.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Cmp>
  struct set_cmp_push_back
  {
    template<class x, class... xs>
    using f = JLN_MP_CONDITIONAL_P_C_T(
      (none_of<push_back<x, Cmp>>::template f<xs...>::value),
      (list<xs..., x>),
      (list<xs...>)
    );
  };

  template<class x, class F>
  struct unique_if_impl
  {
    template<class... xs>
    using f = typename F::template f<x, xs...>;
  };


  template<bool>
  struct unique_impl_select
  {
    template<class Set, class x>
    using f = inherit<Set, list<x>>;
  };

  template<>
  struct unique_impl_select<true>
  {
    template<class Set, class x>
    using f = Set;
  };


  struct unique_next_impl
  {
    template<class Set, class x>
    using f =
      typename unique_impl_select<JLN_MP_IS_BASE_OF(list<x>, Set)>
      ::template f<Set, x>;
  };

  using unique_impl = fold<JLN_MP_SIMPLE_MEMOIZER(unique_next_impl)>;


  template<template<class...> class C, class S>
  struct flat_recursive_unique
  {
    using type = C<>;
  };

  template<template<class...> class C, class s, class x>
  struct flat_recursive_unique<C, inherit<s, x>>
  : _join_select<2>::f<
      C,
      typename flat_recursive_unique<list, s>::type,
      x
    >
  {};

  template<
    template<class...> class C, class s,
    JLN_MP_XS_8(class, JLN_MP_NIL, JLN_MP_COMMA)>
  struct flat_recursive_unique<
    C,
    JLN_MP_REPEAT_8(inherit<, JLN_MP_NIL)
    s
    JLN_MP_XS_8(JLN_MP_COMMA list<, >>, JLN_MP_NIL)
  >
  : _join_select<2>::f<
      C,
      typename flat_recursive_unique<list, s>::type,
      list<JLN_MP_XS_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>
    >
  {};

  template<
    template<class...> class C, class s,
    JLN_MP_XS_32(class, JLN_MP_NIL, JLN_MP_COMMA)>
  struct flat_recursive_unique<
    C,
    JLN_MP_REPEAT_32(inherit<, JLN_MP_NIL)
    s
    JLN_MP_XS_32(JLN_MP_COMMA list<, >>, JLN_MP_NIL)
  >
  : _join_select<2>::f<
      C,
      typename flat_recursive_unique<list, s>::type,
      list<JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>
    >
  {};


  struct start_recursive_unique
  {
    using type = inherit<>;
  };
}

namespace jln::mp
{
  template<class C>
  struct unique_if<same<>, C>
  {
    template<class... xs>
    using f = typename detail::flat_recursive_unique<
      C::template f,
      typename detail::unique_impl
        ::f<inherit<>, xs...>
    >::type;
  };

#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_DEBUG
  template<template<class...> class C>
  struct unique_if<same<>, lift<C>>
  {
    template<class... xs>
    using f = typename detail::flat_recursive_unique<
      C,
      typename detail::unique_impl
        ::f<inherit<>, xs...>
    >::type;
  };
#endif
}
/// \endcond
