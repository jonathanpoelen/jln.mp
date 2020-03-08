#pragma once

#include "transform.hpp"
#include "../utility/same_as.hpp"
#include "../number/operators.hpp"
#include "../../algorithm/count.hpp"


namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using count_if = transform<Pred, add0<contract_barrier<assume_number<C>>>>;

  template<class x, class C = identity>
  using count = contract<mp::count<x, assume_number<C>>>;
}
