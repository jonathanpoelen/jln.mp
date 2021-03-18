#pragma once

#include <jln/mp/smp/functional/recursively.hpp>
#include <jln/mp/smp/functional/if.hpp>
#include <jln/mp/functional/while.hpp>

namespace jln::mp::smp
{
  template<class Pred, class F, class C = identity>
  using while_ = recursively<if_<Pred, F, stop_recursion>, C>;

  template<class Pred, class F, class C = listify>
  using while_xs = recursively<if_<Pred, F, stop_recursion>, C>;
}
