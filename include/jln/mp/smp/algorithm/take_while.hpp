#pragma once

#include "index.hpp"
#include "../list/take.hpp"
#include "../functional/lift.hpp"
#include "../functional/tee.hpp"
#include "../functional/invoke_twice.hpp"
#include "../utility/always.hpp"
#include "../../algorithm/take_while.hpp"

namespace jln::mp::smp
{
  template<class Pred, class C = listify, class NC = C>
  using take_while = invoke_twice<index_if<
    Pred,
    contract<mp::tee<mp::identity, mp::always<C>, lift<take>>>,
    always<NC>>>;
}
