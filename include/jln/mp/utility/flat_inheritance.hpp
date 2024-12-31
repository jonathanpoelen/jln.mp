// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

namespace jln::mp
{
  /// \ingroup utility

  /// Class that inherits all \c Bases types.
  /// This used with \c JLN_MP_IS_BASE_OF() makes a really fast version of \c set_contains.
  /// \code
  ///   class A;
  ///   class B;
  ///   class C;
  ///   using set = mp::flat_inheritance<A, B, C>;
  ///
  ///   using T = ...;
  ///   if constexpr (JLN_MP_IS_BASE_OF(T, set)) {
  ///     ...
  ///   }
  /// \endcode
  template<class... Bases>
  struct flat_inheritance : Bases...
  {};
}
