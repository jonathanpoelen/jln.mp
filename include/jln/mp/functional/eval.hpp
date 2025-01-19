// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>

// note: __cpp_nontype_template_args >= 201911,
// but clang does not have this value because it does not fully support NTTP
#if __cplusplus >= 202002L \
  && defined(__cpp_nontype_template_parameter_auto) \
  && __cpp_nontype_template_parameter_auto >= 201606L
namespace jln::mp
{
  /// \ingroup functional

  /// Invokes a lambda function.
  /// \treturn \value
  template<auto F, class C = identity>
  struct eval
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, decltype(F.template operator()<xs...>()));
  };

  namespace emp
  {
    template<auto F, class... xs>
    using eval = decltype(F.template operator()<xs...>());
  }

  /// \cond
  template<auto F>
  struct eval<F, identity>
  {
    template<class... xs>
    using f = decltype(F.template operator()<xs...>());
  };
  /// \endcond
}
#endif
