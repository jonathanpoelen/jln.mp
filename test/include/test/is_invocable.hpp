#pragma once

#include "jln/mp/number/number.hpp"
#include "jln/mp/functional/is_invocable.hpp"

namespace
{
namespace ut
{
  template<class F, class... xs>
  void invocable()
  {
    jln::mp::true_ x = jln::mp::emp::is_invocable<F, xs...>{};
    (void)x;
  }

  template<class F, class... xs>
  void not_invocable()
  {
    jln::mp::false_ x = jln::mp::emp::is_invocable<F, xs...>{};
    (void)x;
  }
}
}
