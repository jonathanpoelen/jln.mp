#pragma once

#include "transform.hpp"
#include "../utility/same_as.hpp"
#include "../number/operators.hpp"
#include "../../algorithm/count.hpp"


namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using count_if = transform<Pred, add0<assume_number_barrier<C>>>;

  template<class x, class C = identity>
  using count = contract<mp::count<x, assume_number<C>>>;
}
