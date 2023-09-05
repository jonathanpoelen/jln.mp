// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/set/set_contains.hpp>
#include <jln/mp/number/number.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct set_push_front_select;

    template<class S, class x, class = number<0>>
    struct set_push_front_impl;
  }
  /// \endcond

  /// \ingroup set

  /// Appends \c x to the beginning of the \set whose elements are \c xs if not already in \c xs.
  /// \treturn \set
  /// \pre `emp::unique<xs...> == list<xs...>`
  /// \post \c emp::is_unique<result>
  /// \see set_push_back, set_push_front_elements
  template<class x, class C = listify>
  struct set_push_front
  {
    template<class... xs>
    using f = typename detail::set_push_front_select<JLN_MP_SET_CONTAINS(x, xs...)>
      ::template f<JLN_MP_TRACE_F(C), x, xs...>;
  };

  namespace emp
  {
    template<class Set, class x>
    using set_push_front = typename detail::set_push_front_impl<Set, x>::type;
  }
}


/// \cond
#include <jln/mp/set/set_push_back.hpp>

namespace jln::mp::detail
{
  template<>
  struct set_push_front_select<false>
  {
    template<class C, class... xs>
    using f = typename C::template f<xs...>;
  };

  template<>
  struct set_push_front_select<true> : set_push_back_select<true>
  {};

  template<class L, class x, class>
  struct set_push_front_impl
  {
    using type = L;
  };

  template<class... xs, class x>
  struct set_push_front_impl<list<xs...>, x, number<JLN_MP_SET_CONTAINS(x, xs...)>>
  {
    using type = list<x, xs...>;
  };
}
/// \endcond
