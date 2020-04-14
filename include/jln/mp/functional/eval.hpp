#pragma once

#include "identity.hpp"
#include "call.hpp"

namespace jln::mp
{
#ifdef __cpp_nontype_template_parameter_class
#if __cpp_nontype_template_parameter_class >= 201806L
  template<auto F, class C = identity>
  struct eval
  {
    template<class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) < 1000000,
      C, decltype(F.template operator()<xs...>()));
  };

  namespace emp
  {
    template<auto F, class... xs>
    using eval = decltype(F.template operator()<xs...>());
  }
#endif
#endif
}
