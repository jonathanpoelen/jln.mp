#pragma once

#include <jln/mp/smp/list/drop_while.hpp>
#include <jln/mp/smp/functional/not_fn.hpp>
#include <jln/mp/smp/list/is_empty.hpp>
#include <jln/mp/algorithm/any_of.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using any_of = drop_while<not_fn<Pred>, is_empty<not_<C>>>;
}
