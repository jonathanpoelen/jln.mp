#pragma once

#include "transform.hpp"
#include "../list/join.hpp"
#include "../functional/fork.hpp"
#include "../number/to_bool.hpp"
#include "../utility/same_as.hpp"
#include "../../algorithm/count.hpp"


namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using count_if = contract<mp::transform<
    try_subcontract<contract_barrier<assume_unary<Pred>>, to_bool<>>,
    mp::monadic_xs<mp::add0<assume_unary<C>>>>>;

  template<class x, class C = identity>
  using count = contract<mp::count<x, subcontract<C>>>;
}
