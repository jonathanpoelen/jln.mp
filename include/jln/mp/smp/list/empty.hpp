#pragma once

#include "../number/operators.hpp"
#include "../list/size.hpp"
#include "../../list/empty.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using empty = valid_contract<mp::empty<assume_number<C>>>;
}
