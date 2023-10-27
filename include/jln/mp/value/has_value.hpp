// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/number/number.hpp>

namespace jln::mp
{
  /// \ingroup value

#if !JLN_MP_FEATURE_CONCEPTS || !JLN_MP_GCC
  /// \cond
  namespace detail
  {
    template<class x, class = void>
    struct _has_value;
  }
  /// \endcond

  /// Checks whether \c x has a value member.
  /// \treturn \bool
  template<class C = identity>
  struct has_value
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_has_value<x>::type);
  };

  namespace emp
  {
    template<class x>
    using has_value = typename detail::_has_value<x>::type;

    template<class x>
    inline constexpr bool has_value_v = detail::_has_value<x>::type::value;
  }

  /// \cond
  template<>
  struct has_value<identity>
  {
    template<class x>
    using f = typename detail::_has_value<x>::type;
  };
  /// \endcond

#else

  template<class C = identity>
  struct has_value
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<requires{ x::value; }>);
  };

  namespace emp
  {
    template<class x>
    using has_value = number<requires{ x::value; }>;

    template<class x>
    inline constexpr bool has_value_v = requires{ x::value; };
  }

  /// \cond
  template<>
  struct has_value<identity>
  {
    template<class x>
    using f = number<requires{ x::value; }>;
  };
  /// \endcond

#undef JLN_MP_HAS_TYPE

#endif
}

#if !JLN_MP_FEATURE_CONCEPTS || !JLN_MP_GCC
#include <type_traits>

/// \cond
namespace jln::mp::detail
{
  template<class x, class>
  struct _has_value
  {
    using type = false_;
  };

  template<class x>
  struct _has_value<x, decltype(void(x::value))>
  {
    using type = true_;
  };
}
/// \endcond
#endif
