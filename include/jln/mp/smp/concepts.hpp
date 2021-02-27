#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/number/to_bool.hpp>
#include <jln/mp/functional/tee.hpp>

namespace jln::mp::smp::concepts
{
  template<class Pred, class TC = mp::identity, class FC = mp::always<false_>>
  using predicate = try_<mp::tee<Pred, mp::to_bool<>>, TC, FC>;
}
