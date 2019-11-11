#pragma once

#include "remove_if.hpp"
#include "../utility/same_as.hpp"
#include "../../algorithm/remove.hpp"

namespace jln::mp::smp
{
  template<class T, class C = listify>
  using remove = valid_contract<mp::remove<T, subcontract<C>>>;
}
