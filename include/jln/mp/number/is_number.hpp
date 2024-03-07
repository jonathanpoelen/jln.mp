// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
#if !JLN_MP_FAST_ALIAS_ON_VARIABLE_TEMPLATE
  /// \cond
  namespace detail
  {
    template<class x>
    struct is_number_impl;
  }
  /// \endcond
#endif

  /// \ingroup number

  namespace emp
  {
    template<class x>
    constexpr bool is_number_v = false;

    template<int_ n>
    constexpr bool is_number_v<number<n>> = true;
  }

  /// Checks whether a \value is a \number.
  /// \treturn \bool
  template<class C = identity>
  struct is_number
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_NUMBER_FROM_REGULAR_VARIABLE_TEMPLATE_OR_TYPE(is_number, x));
  };

  namespace emp
  {
    template<class x>
    using is_number = JLN_MP_NUMBER_FROM_REGULAR_VARIABLE_TEMPLATE_OR_TYPE(is_number, x);
  }

  /// \cond
  template<>
  struct is_number<identity>
  {
    template<class x>
    using f = JLN_MP_NUMBER_FROM_REGULAR_VARIABLE_TEMPLATE_OR_TYPE(is_number, x);
  };
  /// \endcond
}

#if !JLN_MP_FAST_ALIAS_ON_VARIABLE_TEMPLATE
/// \cond
namespace jln::mp::detail
{
  template<class x>
  struct is_number_impl
  {
    using type = false_;
  };

  template<int_ x>
  struct is_number_impl<number<x>>
  {
    using type = true_;
  };
}
/// \endcond
#endif
