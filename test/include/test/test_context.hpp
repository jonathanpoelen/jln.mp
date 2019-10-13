#pragma once

#include "./is_invocable.hpp"
#include "./is_same.hpp"
#include "jln/mp/functional/call.hpp"
#include "jln/mp/functional/always.hpp"
#include "jln/mp/functional/sfinae.hpp"

namespace {
inline namespace TU
{
  using namespace jln::mp;

  template<class Mp, class Smp>
  struct test_context
  {
    IS_SAME(Smp, sfinae<Mp>);
    IS_SAME(Smp, sfinae<Smp>);

    template<class R, class... xs>
    test_context& test()
    {
      IS_INVOCABLE(Smp, xs...);
      R() = call<Mp, xs...>();
      R() = call<Smp, xs...>();
      return *this;
    }

    template<class... xs>
    test_context& not_invocable()
    {
      not IS_INVOCABLE(Smp, xs...);
      return *this;
    }
  };
}
}
