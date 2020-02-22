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
  using count_if = valid_contract<mp::transform<
    try_subcontract<Pred, to_bool<>>,
    mp::monadic_xs<mp::add0<subcontract<C>>>>>;

  template<class x, class C = identity>
  using count = valid_contract<mp::count<x, subcontract<C>>>;
}
