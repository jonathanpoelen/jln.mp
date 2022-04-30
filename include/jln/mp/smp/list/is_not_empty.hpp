#pragma once

#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/list/is_not_empty.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using is_not_empty = contract<mp::is_not_empty<assume_positive_number<C>>>;
}
