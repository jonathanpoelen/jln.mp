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
    template<template<class...> class Tpl, class T>
    struct is_specialization_of_impl;
  }
  /// \endcond
#endif

  /// \ingroup trait

  namespace emp
  {
    template<template<class...> class Tpl, class T>
    inline constexpr bool is_specialization_of_v = false;

    template<template<class...> class Tpl, class... Ts>
    inline constexpr bool is_specialization_of_v<Tpl, Tpl<Ts...>> = true;
  }

  /// Checks whether \c x is \c Tpl<xs...>
  /// \treturn \bool
  template<template<class...> class Tpl, class C = identity>
  struct is_specialization_of
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C,
      JLN_MP_NUMBER_FROM_REGULAR_VARIABLE_TEMPLATE_OR_TYPE(is_specialization_of, Tpl, x));
  };

  namespace emp
  {
    template<template<class...> class Tpl, class x>
    using is_specialization_of
      = JLN_MP_NUMBER_FROM_REGULAR_VARIABLE_TEMPLATE_OR_TYPE(is_specialization_of, Tpl, x);
  }

  /// \cond
  template<template<class...> class Tpl>
  struct is_specialization_of<Tpl, identity>
  {
    template<class x>
    using f = JLN_MP_NUMBER_FROM_REGULAR_VARIABLE_TEMPLATE_OR_TYPE(is_specialization_of, Tpl, x);
  };
  /// \endcond
}

#if !JLN_MP_FAST_ALIAS_ON_VARIABLE_TEMPLATE
/// \cond
namespace jln::mp::detail
{
  template<template<class...> class Tpl, class T>
  struct is_specialization_of_impl
  {
    using type = false_;
  };

  template<template<class...> class Tpl, class... Ts>
  struct is_specialization_of_impl<Tpl, Tpl<Ts...>>
  {
    using type = true_;
  };
}
/// \endcond
#endif
