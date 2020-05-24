#pragma once

#include "remove.hpp"
#include "../functional/tee.hpp"
#include "../number/operators.hpp"
#include "../../algorithm/copy.hpp"


namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using copy_if = remove_if<try_<
    mp::tee<assume_unary<Pred>, mp::not_<>>>, C>;

  template<class x, class C = listify>
  using copy = contract<mp::copy<x, subcontract<C>>>;
}
