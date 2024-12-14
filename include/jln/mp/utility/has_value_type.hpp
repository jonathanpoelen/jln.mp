// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/number/number.hpp>

namespace jln::mp
{
  /// \ingroup trait

#if !JLN_MP_FEATURE_CONCEPTS || !JLN_MP_REQUIRES_AS_FAST_SFINAE
  /// \cond
  namespace detail
  {
    template<class x, class = void>
    struct _has_value_type;
  }
  /// \endcond

  /// Checks whether \c x has a type member.
  /// \treturn \bool
  template<class C = identity>
  struct has_value_type
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_has_value_type<x>::type);
  };

  namespace emp
  {
    template<class x>
    using has_value_type = typename detail::_has_value_type<x>::type;

    template<class x>
    inline constexpr bool has_value_type_v = detail::_has_value_type<x>::type::value;
  }

  /// \cond
  template<>
  struct has_value_type<identity>
  {
    template<class x>
    using f = typename detail::_has_value_type<x>::type;
  };
  /// \endcond

#else

  template<class C = identity>
  struct has_value_type
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<requires{ typename x::value_type; }>);
  };

  namespace emp
  {
    template<class x>
    using has_value_type = number<requires{ typename x::value_type; }>;

    template<class x>
    inline constexpr bool has_value_type_v = requires{ typename x::value_type; };
  }

  /// \cond
  template<>
  struct has_value_type<identity>
  {
    template<class x>
    using f = number<requires{ typename x::value_type; }>;
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
  struct _has_value_type
  {
    using type = false_;
  };

  template<class x>
  struct _has_value_type<x, std::void_t<typename x::value_type>>
  {
    using type = true_;
  };
}
/// \endcond
#endif
