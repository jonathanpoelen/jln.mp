#pragma once

#include <jln/mp/smp/algorithm/index.hpp>
#include <jln/mp/smp/list/take.hpp>
#include <jln/mp/smp/functional/lift.hpp>
#include <jln/mp/smp/functional/tee.hpp>
#include <jln/mp/smp/functional/invoke_twice.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/algorithm/take_while.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = listify, class NC = C>
  using take_while = invoke_twice<index_if<
    Pred,
    contract<mp::tee<mp::identity, mp::always<C>, lift<take>>>,
    always<NC>>>;
}
