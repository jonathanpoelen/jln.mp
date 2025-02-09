// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/fold.hpp>
#include <jln/mp/set/set_push_back.hpp>
#include <jln/mp/functional/continuation.hpp>


namespace jln::mp
{
  /// \ingroup set

  /// Appends to the end of the \set \c Set the elements of \c xs which are not already in \c Set.
  /// \treturn \set
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   fold<cfe<emp::set_push_back>>::f<xs...>
  ///   \endcode
  /// \pre \c emp::is_unique<Set>
  /// \post \c emp::is_unique<result>
  /// \see set_push_back, set_push_front_elements
#ifdef JLN_MP_DOXYGENATING
  template<class C = listify>
  struct set_push_back_elements
  {
    template<class Set, class... xs>
    using f;
  };
#else
  template<class C = listify>
  using set_push_back_elements = fold<
    cfe<emp::set_push_back>,
    detail::optimize_useless_unpack_t<unpack<C>>
  >;
#endif

  namespace emp
  {
    template<class Set, class... xs>
    using set_push_back_elements = typename mp::set_push_back_elements<>::template f<Set, xs...>;
  }
}
