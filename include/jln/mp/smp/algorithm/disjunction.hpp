#pragma once

#include <jln/mp/smp/algorithm/any_of.hpp>
#include <jln/mp/smp/number/to_bool.hpp>
#include <jln/mp/algorithm/disjunction.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using disjunction = any_of<to_bool<>, C>;
}
