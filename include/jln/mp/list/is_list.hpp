// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/list.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/functional/identity.hpp>

namespace jln::mp
{
#if !JLN_MP_FAST_ALIAS_ON_VARIABLE_TEMPLATE
  /// \cond
  namespace detail
  {
    template<class x>
    struct is_list_impl;
  }
  /// \endcond
#endif

  /// \ingroup list

  namespace emp
  {
    template<class x>
    constexpr bool is_list_v = false;

    template<class... xs>
    constexpr bool is_list_v<list<xs...>> = true;
  }

  /// Checks whether \c x is a \list.
  /// \treturn \bool
  template<class C = identity>
  struct is_list
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C,
      JLN_MP_NUMBER_FROM_REGULAR_VARIABLE_TEMPLATE_OR_TYPE(is_list, x));
  };

  namespace emp
  {
    template<class x, class C = mp::identity>
    using is_list = JLN_MP_CALL_TRACE(C,
      JLN_MP_NUMBER_FROM_REGULAR_VARIABLE_TEMPLATE_OR_TYPE(is_list, x));
  }

  /// \cond
  template<>
  struct is_list<identity>
  {
    template<class x>
    using f = JLN_MP_NUMBER_FROM_REGULAR_VARIABLE_TEMPLATE_OR_TYPE(is_list, x);
  };
  /// \endcond
} // namespace jln::mp


#include <jln/mp/number/number.hpp>

#if !JLN_MP_FAST_ALIAS_ON_VARIABLE_TEMPLATE
/// \cond
namespace jln::mp::detail
{
  template<class x>
  struct is_list_impl
  {
    using type = false_;
  };

  template<class... xs>
  struct is_list_impl<list<xs...>>
  {
    using type = true_;
  };
} // namespace jln::mp::detail
/// \endcond
#endif
