#pragma once

#include <jln/mp/smp/algorithm/any_of.hpp>
#include <jln/mp/algorithm/none_of.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using none_of = any_of<Pred, not_<C>>;
}
