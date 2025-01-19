// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/not.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/utility/inherit.hpp>
#include <jln/mp/utility/is_base_of.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/list/list.hpp>

namespace jln::mp
{
  /// \cond
#define JLN_MP_SET_CONTAINS_BASE(x, ...) JLN_MP_IS_BASE_OF(list<x>, __VA_ARGS__)
#define JLN_MP_SET_CONTAINS(x, ...) JLN_MP_SET_CONTAINS_BASE(x, inherit_safely<__VA_ARGS__>)
  /// \endcond

  /// \ingroup set

  /// Checks if \c x is an element of the \set whose elements are \c xs.
  /// \treturn \bool
  /// \pre `emp::unique<xs...> == list<xs...>`
  template<class x, class C = identity>
  struct set_contains
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_SET_CONTAINS(x, xs...)>);
  };

  /// Checks if \c x is not an element of the \set whose elements are \c xs.
  /// \treturn \bool
  /// \pre `emp::unique<xs...> == list<xs...>`
  template<class x, class C = identity>
  using set_not_contains = set_contains<x, not_<C>>;

  namespace emp
  {
    /// \c true if \c x is an element of the set \c xs, \c false otherwise.
    template<class x, class... xs>
    inline constexpr bool set_contains_xs_v = JLN_MP_SET_CONTAINS(x, xs...);

    /// \c true if \c x is an element of the set \c Set, \c false otherwise.
    template<class Set, class x>
    inline constexpr bool set_contains_v = JLN_MP_SET_CONTAINS_BASE(
      x, typename detail::_unpack<mp::lift<inherit_safely>, Set>::type
    );

    /// \c true if \c x is an element of all \set \c Sets, \c false otherwise.
    template<class x, class... Sets>
    inline constexpr bool set_all_contains_v = (JLN_MP_SET_CONTAINS_BASE(
      x, typename detail::_unpack<mp::lift<inherit_safely>, Sets>::type
    ) && ...);

    /// \c true if \c x is an element of any \set \c Sets, \c false otherwise.
    template<class x, class... Sets>
    inline constexpr bool set_any_contains_v = (JLN_MP_SET_CONTAINS_BASE(
      x, typename detail::_unpack<mp::lift<inherit_safely>, Sets>::type
    ) || ...);

    /// \c true if \c x is an element of none \set \c Sets, \c false otherwise.
    template<class x, class... Sets>
    inline constexpr bool set_none_contains_v = !set_any_contains_v<x, Sets...>;

    /// \c true_ if \c x is an element of the set \c Set, \c false_ otherwise.
    template<class Set, class x>
    using set_contains = number<set_contains_v<Set, x>>;

    /// \c true_ if \c x is an element of the set \c Set, \c false_ otherwise.
    template<class Set, class x>
    using set_not_contains = number<!set_contains_v<Set, x>>;

    /// \c true_ if \c x is an element of all \set \c Sets, \c false_ otherwise.
    template<class x, class... Sets>
    using set_all_contains = number<set_all_contains_v<x, Sets...>>;

    /// \c true_ if \c x is an element of any \set \c Sets, \c false_ otherwise.
    template<class x, class... Sets>
    using set_any_contains = number<set_any_contains_v<x, Sets...>>;

    /// \c true_ if \c x is an element of none \set \c Sets, \c false_ otherwise.
    template<class x, class... Sets>
    using set_none_contains = number<!set_any_contains_v<x, Sets...>>;
  }

  /// Checks if \c x is an element of all \set \c Sets.
  /// \treturn \bool
  /// \pre `emp::unique<Sets> && ...`
  template<class x, class C = identity>
  struct set_all_contains
  {
    template<class... Sets>
    using f = JLN_MP_CALL_TRACE(C, number<emp::set_all_contains_v<x, Sets...>>);
  };

  /// Checks if \c x is an element of any \set \c Sets.
  /// \treturn \bool
  /// \pre `emp::unique<Sets> && ...`
  template<class x, class C = identity>
  struct set_any_contains
  {
    template<class... Sets>
    using f = JLN_MP_CALL_TRACE(C, number<emp::set_any_contains_v<x, Sets...>>);
  };

  /// Checks if \c x is an element of none \set \c Sets.
  /// \treturn \bool
  /// \pre `emp::unique<Sets> && ...`
  template<class x, class C = identity>
  struct set_none_contains
  {
    template<class... Sets>
    using f = JLN_MP_CALL_TRACE(C, number<!emp::set_any_contains_v<x, Sets...>>);
  };
}

/// \cond
namespace jln::mp
{
  template<class x>
  struct set_contains<x, identity>
  {
    template<class... xs>
    using f = number<JLN_MP_SET_CONTAINS(x, xs...)>;
  };

  template<class x, class C>
  struct set_contains<x, not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<!JLN_MP_SET_CONTAINS(x, xs...)>);
  };

  template<class x>
  struct set_contains<x, not_<identity>>
  {
    template<class... xs>
    using f = number<!JLN_MP_SET_CONTAINS(x, xs...)>;
  };

  template<class x>
  struct set_all_contains<x, identity>
  {
    template<class... Sets>
    using f = number<emp::set_all_contains_v<x, Sets...>>;
  };

  template<class x>
  struct set_any_contains<x, identity>
  {
    template<class... Sets>
    using f = number<emp::set_any_contains_v<x, Sets...>>;
  };

  template<class x>
  struct set_none_contains<x, identity>
  {
    template<class... Sets>
    using f = number<!emp::set_any_contains_v<x, Sets...>>;
  };
}
/// \endcond
