// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/value/val.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/functional/identity.hpp>

namespace jln::mp
{
#if !JLN_MP_FAST_ALIAS_ON_VARIABLE_TEMPLATE
  /// \cond
  namespace detail
  {
    template<class x>
    struct is_val_impl;
  }
  /// \endcond
#endif

  /// \ingroup value

  namespace emp
  {
    template<class x>
    inline constexpr bool is_val_v = false;

#if JLN_MP_ENABLE_TPL_PARAM_AUTO && (!JLN_MP_DEBUG || JLN_MP_CLANG_LIKE)
    template<auto x>
    inline constexpr bool is_val_v<val<x>> = true;
#else
    template<class T, T x>
    inline constexpr bool is_val_v<typed_value<T, x>> = true;
#endif
  }

  /// Checks whether \c x is a \val.
  /// \treturn \bool
  template<class C = identity>
  struct is_val
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_NUMBER_FROM_REGULAR_VARIABLE_TEMPLATE_OR_TYPE(is_val, x));
  };

  namespace emp
  {
    template<class x>
    using is_val = JLN_MP_NUMBER_FROM_REGULAR_VARIABLE_TEMPLATE_OR_TYPE(is_val, x);
  }

  /// \cond
  template<>
  struct is_val<identity>
  {
    template<class x>
    using f = JLN_MP_NUMBER_FROM_REGULAR_VARIABLE_TEMPLATE_OR_TYPE(is_val, x);
  };
  /// \endcond
}


#if !JLN_MP_FAST_ALIAS_ON_VARIABLE_TEMPLATE
/// \cond
namespace jln::mp::detail
{
  template<class x>
  struct is_val_impl
  {
    using type = false_;
  };

#if JLN_MP_ENABLE_TPL_PARAM_AUTO && (!JLN_MP_DEBUG || JLN_MP_CLANG_LIKE)
  template<auto x>
  struct is_val_impl<val<x>>
#else
  template<class T, T x>
  struct is_val_impl<typed_value<T, x>>
#endif
  {
    using type = true_;
  };
}
/// \endcond
#endif
