#pragma once

namespace jln::mp
{
#ifdef __cpp_nontype_template_parameter_auto
#if __cpp_nontype_template_parameter_auto >= 201606L
  template<auto F>
  struct eval
  {
    template<class... xs>
    using f = decltype(F.template operator()<xs...>());
  };
#endif
#endif
}
