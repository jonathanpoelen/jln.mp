#pragma once

#include <jln/mp/smp/algorithm/copy.hpp>
#include <jln/mp/smp/algorithm/remove.hpp>
#include <jln/mp/smp/functional/tee.hpp>
#include <jln/mp/algorithm/partition.hpp>

namespace jln::mp::smp
{
  template<class Pred, class F = listify, class C = listify>
  using partition_with = tee<copy_if<Pred, F>, remove_if<Pred, F>,
    assume_binary_list_barrier<C>>;

  template<class Pred, class C = listify>
  using partition = partition_with<Pred, listify, C>;
}
