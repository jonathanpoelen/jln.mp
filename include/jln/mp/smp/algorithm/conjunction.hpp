#pragma once

#include <jln/mp/smp/algorithm/all_of.hpp>
#include <jln/mp/smp/number/to_bool.hpp>
#include <jln/mp/algorithm/conjunction.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using conjunction = all_of<to_bool<>, C>;
}
