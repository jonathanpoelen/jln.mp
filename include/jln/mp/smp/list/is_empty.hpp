#pragma once

#include "../number/operators.hpp"
#include "../list/size.hpp"
#include "../../list/is_empty.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using is_empty = contract<mp::is_empty<assume_number<C>>>;
}
