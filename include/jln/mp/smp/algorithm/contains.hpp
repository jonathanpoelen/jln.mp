#pragma once

#include <jln/mp/smp/algorithm/any_of.hpp>
#include <jln/mp/smp/utility/is_not.hpp>
#include <jln/mp/algorithm/contains.hpp>

namespace jln::mp::smp
{
  template<class x, class C = identity>
  using contains = any_of<contract_barrier<mp::is<x>>, C>;
}
