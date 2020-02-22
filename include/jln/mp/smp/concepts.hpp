#pragma once

#include "../utility/always.hpp"
#include "../number/to_bool.hpp"
#include "../functional/contract.hpp"

namespace jln::mp::smp::concepts
{
  // TODO output_type<Pred> = number -> if_<subcontract<Pred>, ....>
  template<class Pred, class TC = mp::identity, class FC = mp::always<false_>>
  using predicate = try_invoke<
    mp::fork<subcontract<Pred>, mp::to_bool<>>,
    TC, FC>;
}
