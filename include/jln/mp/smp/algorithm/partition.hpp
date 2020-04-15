#pragma once

#include "copy.hpp"
#include "remove.hpp"
#include "../functional/fork.hpp"
#include "../../algorithm/partition.hpp"

namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using partition = fork<remove_if<Pred>, copy_if<Pred>,
    assume_binary_list_barrier<C>>;
}
