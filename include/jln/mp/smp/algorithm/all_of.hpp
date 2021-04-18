#pragma once

#include <jln/mp/smp/algorithm/drop_while.hpp>
#include <jln/mp/smp/list/is_empty.hpp>
#include <jln/mp/smp/functional/not_fn.hpp>
#include <jln/mp/algorithm/all_of.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using all_of = drop_while<Pred, is_empty<C>>;
}
