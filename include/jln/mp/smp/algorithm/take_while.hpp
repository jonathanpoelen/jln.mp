#pragma once

#include "index.hpp"
#include "../list/take.hpp"
#include "../functional/function.hpp"
#include "../functional/fork.hpp"
#include "../functional/fork_front.hpp"
#include "../utility/always.hpp"
#include "../../algorithm/take_while.hpp"

namespace jln::mp::smp
{
  template<class Pred, class C = listify, class NC = C>
  using take_while = fork_front<index_if<
    Pred,
    contract<mp::fork<mp::identity, mp::always<C>, cfe<take>>>,
    always<NC>>>;
}
