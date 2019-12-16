#pragma once

#include "index.hpp"
#include "../list/take.hpp"
#include "../functional/bind.hpp"
#include "../functional/fork.hpp"
#include "../functional/fork_front.hpp"
#include "../utility/always.hpp"
#include "../../algorithm/take_while.hpp"

namespace jln::mp::smp
{
  template<class Pred, class C = listify, class NC = C>
  using take_while = detail::sfinae<mp::take_while<
      subcontract_barrier<Pred>, subcontract_barrier<C>, subcontract_barrier<NC>>>;
}
