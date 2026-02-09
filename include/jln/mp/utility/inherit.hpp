// SPDX-FileCopyrightText: 2025 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/list.hpp>
#include <jln/mp/detail/compiler.hpp>

namespace jln::mp
{
  JLN_MP_DIAGNOSTIC_PUSH()
#if JLN_MP_GCC >= 1000
  JLN_MP_DIAGNOSTIC_GCC_IGNORE("-Winaccessible-base")
#endif
  JLN_MP_DIAGNOSTIC_MSVC_IGNORE(4584)

  /// \ingroup utility

  /// Class that inherits all \c Bases types.
  /// This used with \c JLN_MP_IS_BASE_OF() makes a really fast version of \c set_contains.
  /// \code
  ///   class A {};
  ///   class B {};
  ///   class C {};
  ///   using set = inherit<A, B, C>;
  ///
  ///   using T = ...;
  ///   if constexpr (JLN_MP_IS_BASE_OF(T, set)) {
  ///     ...
  ///   }
  /// \endcode
  template<class... Bases>
  struct inherit : Bases...
  {};

  /// Class that inherits all \c Bases types wrapped in a \c list<> type.
  /// \code
  ///   class A;
  ///   class B;
  ///   class C;
  ///   using set = inherit_safely<A, B, C>;
  ///
  ///   using T = ...;
  ///   if constexpr (JLN_MP_IS_BASE_OF(list<T>, set)) {
  ///     ...
  ///   }
  /// \endcode
  template<class... Bases>
  struct inherit_safely : list<Bases>...
  {};

  JLN_MP_DIAGNOSTIC_POP()
}
