// SPDX-FileCopyrightText: 2026 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/compiler.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>

/// Uses a compiler builtin or \c std::is_base_if_v.
/// Note: the real signature takes a var args.
#ifdef DOXYGENATING
# define JLN_MP_IS_BASE_OF(Base, Derived)
#elif JLN_MP_CLANG_LIKE || JLN_MP_GCC || JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_base_of)
# define JLN_MP_IS_BASE_OF __is_base_of
#else
# define JLN_MP_IS_BASE_OF(...) std::is_base_of_v<__VA_ARGS__>
# include <type_traits>
#endif

namespace jln::mp
{
  /// \ingroup utility

  /// Wrapper for \c JLN_MP_IS_BASE_OF() / \c std::is_base_of
  /// \treturn \c true_ / \c false_
  template<class Derived, class C = identity>
  struct is_base_of
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_IS_BASE_OF(x, Derived)>);
  };

  namespace emp
  {
    template<class Base, class Derived>
    using is_base_of = number<JLN_MP_IS_BASE_OF(Base, Derived)>;

    template<class Base, class Derived>
    inline constexpr bool is_base_of_v = JLN_MP_IS_BASE_OF(Base, Derived);
  }

  /// \cond
  template<class Derived>
  struct is_base_of<Derived, identity>
  {
    template<class x>
    using f = number<JLN_MP_IS_BASE_OF(x, Derived)>;
  };
  /// \endcond
}
