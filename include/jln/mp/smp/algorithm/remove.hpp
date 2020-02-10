#pragma once

#include "transform.hpp"
#include "../list/join.hpp"
#include "../list/list_wrap_if.hpp"
#include "../utility/same_as.hpp"
#include "../../algorithm/remove.hpp"


namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using remove_if = valid_contract<mp::transform<
    subcontract<list_wrap_if_not<Pred>>,
    mp::monadic_xs<mp::join<subcontract<C>>>>>;

  template<class x, class C = listify>
  using remove = valid_contract<mp::remove<x, subcontract<C>>>;
}
