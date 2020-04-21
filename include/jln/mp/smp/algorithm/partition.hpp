#pragma once

#include "copy.hpp"
#include "remove.hpp"
#include "../functional/fork.hpp"
#include "../../algorithm/partition.hpp"

namespace jln::mp::smp
{
  template<class Pred, class F = listify, class C = listify>
  using partition_with = fork<remove_if<Pred, F>, copy_if<Pred, F>,
    assume_binary_list_barrier<C>>;

  template<class Pred, class C = listify>
  using partition = partition_with<Pred, listify, C>;
}
