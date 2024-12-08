// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/join.hpp>
#include <jln/mp/list/wrap_in_list.hpp>
#include <jln/mp/set/set_contains.hpp>
#include <jln/mp/set/set_push_back.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class L, class C = listify>
    struct set_difference_impl
    {};
  }
  /// \endcond

  /// \ingroup set

  /// Removes the elements of the list \c L that appear in any of the sets \c Sets.
  /// \treturn \set
  /// \pre `emp::is_unique<Sets> && ...`
  /// \post \c emp::is_unique<result>
  template<class C = listify>
  struct set_difference
  {
    template<class L, class... Sets>
    using f = typename detail::set_difference_impl<L>::template f<C, Sets...>;
  };

  namespace emp
  {
    template<class L, class... Sets>
    using set_difference = typename detail::set_difference_impl<L>::template f<listify, Sets...>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<template<class...> class List, class... xs>
  struct set_difference_impl<List<xs...>>
  {
    template<class C, class... Sets>
    using f = typename join<C>::template f<
      typename wrap_in_list_c<!emp::set_any_contains_v<xs, Sets...>>
      ::template f<xs>...
    >;
  };
}
/// \endcond
