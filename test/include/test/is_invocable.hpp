#pragma once

#include "jln/mp/number/number.hpp"
#include "jln/mp/functional/is_invocable.hpp"
#include "jln/cxx/diagnostic.hpp"

namespace ut
{
namespace
{
  template<class F, class... xs>
  void invocable()
  {
    jln::mp::true_ x = jln::mp::emp::is_invocable<F, xs...>{};
    (void)x;
  }

  JLN_DIAGNOSTIC_PUSH
  JLN_DIAGNOSTIC_CLANG_IGNORE("-Wunused-template")
  template<class F, class... xs>
  void not_invocable()
  {
    jln::mp::false_ x = jln::mp::emp::is_invocable<F, xs...>{};
    (void)x;
  }
  JLN_DIAGNOSTIC_POP
}
}
