#pragma once

#include "../algorithm/any_of.hpp"
#include "../utility/same_as.hpp"
#include "../../algorithm/contains.hpp"

namespace jln::mp::smp
{
  template<class x, class C = identity>
  using contains = any_of<contract_barrier<mp::same_as<x>>, C>;
}
