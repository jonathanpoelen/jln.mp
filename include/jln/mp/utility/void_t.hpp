// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/first.hpp>

#if JLN_MP_LAZY_ALIAS
# include <type_traits>
#endif

namespace jln::mp
{
  /// \ingroup trait

  /// Equivalent to \c std::void_t, but always resolved in a lazy way.
  /// This fixes the ambiguity encountered with clang for the following code:
  /// \code
  /// template<class T, class = void> struct Impl;
  /// template<class T> struct Impl<T, emp::void_t<T::foo>> {};
  /// template<class T> struct Impl<T, emp::void_t<T::bar>> {}; // redefinition of Impl<T, void> with std::void_t
  /// \endcode
  /// This behavior is also possible with \c always when
  /// the macro \c JLN_MP_FORCE_LAZY_ALIAS is set to \c 0.
#ifdef JLN_MP_DOXYGENATING
  // not implemented, just for doc generating...
  struct void_t;
#endif

  namespace emp
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using void_t = void;
#elif JLN_MP_LAZY_ALIAS
    using std::void_t;
#else
    template<class... xs>
    using void_t = typename detail::first<void, list<xs...>>::type;
#endif
  }
}
