#pragma once

#include "transform.hpp"
#include "../list/join.hpp"
#include "../list/wrap_in_list.hpp"
#include "../utility/is.hpp"
#include "../../algorithm/remove.hpp"


namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using remove_if = contract<mp::transform<
    subcontract<wrap_in_list_if_not<assume_unary_barrier<Pred>>>,
    mp::monadic_xs<mp::join<subcontract<C>>>>>;

  template<class x, class C = listify>
  using remove = contract<mp::remove<x, subcontract<C>>>;
}
