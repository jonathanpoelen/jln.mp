// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/fold.hpp>
#include <jln/mp/set/set_push_front.hpp>
#include <jln/mp/functional/lift.hpp>


namespace jln::mp
{
  /// \ingroup set

  /// Appends to the beginning of the \set \c Set the elements of \c xs which are not already in \c Set.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   fold<lift<emp::set_push_front>>::f<xs...>
  ///   \endcode
  /// \treturn \set
  /// \pre \c emp::is_unique<Set>
  /// \post \c emp::is_unique<result>
  /// \see set_push_front, set_push_back_elements
#ifdef JLN_MP_DOXYGENATING
  template<class C = listify>
  struct set_push_front_elements
  {
    template<class Set, class... xs>
    using f;
  };
#else
  template<class C = listify>
  using set_push_front_elements = fold<
    lift<emp::set_push_front>,
    detail::optimize_useless_unpack_t<unpack<C>>
  >;
#endif

  namespace emp
  {
    template<class Set, class... xs>
    using set_push_front_elements = typename mp::set_push_front_elements<>::template f<Set, xs...>;
  }
}
