#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
#ifdef __cpp_nontype_template_parameter_class
#if __cpp_nontype_template_parameter_class >= 201806L
  /// \ingroup functional

  /// Invokes a lambda function.
  /// \treturn \value
  template<auto F, class C = identity>
  struct eval
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE((C), decltype(F.template operator()<xs...>()));
  };

  namespace emp
  {
    template<auto F, class... xs>
    using eval = decltype(F.template operator()<xs...>());
  }
#endif
#endif
}
