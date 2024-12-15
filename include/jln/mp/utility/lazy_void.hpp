// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/first.hpp>

namespace jln::mp
{
  /// \ingroup trait

  /// Equivalent to \c std::void_t, but always resolved in a lazy way.
  /// This fixes the ambiguity encountered with clang for the following code:
  /// \code
  /// template<class T, class = void> struct Impl;
  /// template<class T> struct Impl<T, std::void_t<typename T::foo>> {};
  /// template<class T> struct Impl<T, std::void_t<typename T::bar>> {}; // redefinition of Impl<T, void>
  /// \endcode
  /// \c lazy_void can be replaced with \c always<void>::f when
  /// the macro \c JLN_MP_FORCE_LAZY_ALIAS is set to \c 0.
#ifdef JLN_MP_DOXYGENATING
  // not implemented, just for doc generating...
  struct lazy_void;
#endif

  namespace emp
  {
#if JLN_MP_LAZY_ALIAS
    template<class... xs>
    using lazy_void = void;
#elif JLN_MP_ENABLE_TYPE_PACK_ELEMENT
    template<class... xs>
    using lazy_void = __type_pack_element<0, void, xs...>;
#else
    template<class... xs>
    using lazy_void = typename detail::first<void, sizeof(list<xs...>)>::type;
#endif
  }

/// Equivalent to \c emp::lazy_void<xs...> while minimizing template instantiation.
#if JLN_MP_ENABLE_TYPE_PACK_ELEMENT
# define JLN_MP_LAZY_VOID(...) __type_pack_element<0, void, __VA_ARGS__>
#else
# define JLN_MP_LAZY_VOID(...) ::jln::mp::emp::lazy_void<__VA_ARGS__>
#endif
}
