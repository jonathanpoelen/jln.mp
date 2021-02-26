#pragma once

#include "../algorithm/any_of.hpp"
#include "../utility/is.hpp"
#include "../../algorithm/contains.hpp"

namespace jln::mp::smp
{
  template<class x, class C = identity>
  using contains = any_of<contract_barrier<mp::is<x>>, C>;
}
