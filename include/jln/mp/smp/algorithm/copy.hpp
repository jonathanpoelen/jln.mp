#pragma once

#include <jln/mp/smp/algorithm/remove.hpp>
#include <jln/mp/smp/functional/tee.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/algorithm/copy.hpp>


namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using copy_if = remove_if<try_<
    mp::tee<assume_unary<Pred>, mp::not_<>>>, C>;

  template<class x, class C = listify>
  using copy = contract<mp::copy<x, subcontract<C>>>;
}
