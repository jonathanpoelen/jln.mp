#pragma once

#include <jln/mp/smp/algorithm/drop_while.hpp>
#include <jln/mp/smp/functional/not_fn.hpp>
#include <jln/mp/smp/algorithm/index.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/algorithm/any_of.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using any_of = drop_while<not_fn<Pred>, always<true_, C>, always<false_, C>>;
}
