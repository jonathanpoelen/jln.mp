// SPDX-FileCopyrightText: 2026 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/list.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/detail/compiler.hpp>

namespace jln::mp
{
  JLN_MP_DIAGNOSTIC_PUSH()
#if JLN_MP_GCC >= 1000 || JLN_MP_CLANG
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
  /// \warning This class should not be used with algorithms,
  /// as this may interfere with their proper functioning.
  template<class... Bases>
  struct inherit : Bases...
  {};

  /// Class that inherits all \c Bases types wrapped in a \c list<> type.
  /// This used with \c JLN_MP_IS_BASE_OF() makes a really fast version of \c set_contains.
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
  /// \warning This class should not be used with algorithms,
  /// as this may interfere with their proper functioning.
  template<class... Bases>
  struct inherit_safely : list<Bases>...
  {};


  /// \warning This class should not be used with algorithms,
  /// as this may interfere with their proper functioning.
  template<int_t i, class Base>
  struct indexed_item : list<Base>
  {};

  /// Class that inherits all \c Bases types wrapped in \c indexed_item<>.
  /// indexed_inherit is intended to be instantiated with
  /// `JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), indexed_inherit)`.
  /// \warning This class should not be used with algorithms,
  /// as this may interfere with their proper functioning.
  template<class, int_t... ints>
  struct indexed_inherit
  {
    template<class... Bases>
    struct f : indexed_item<ints, Bases>...
    {};
  };

  JLN_MP_DIAGNOSTIC_POP()
}
