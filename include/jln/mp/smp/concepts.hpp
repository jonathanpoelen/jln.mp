#pragma once

#include "../utility/always.hpp"
#include "../number/to_bool.hpp"
#include "../functional/contract.hpp"
#include "../functional/fork.hpp"

namespace jln::mp::smp::concepts
{
  // TODO remove to_bool ?
  
  // TODO output_type<Pred> = number -> if_<subcontract<Pred>, ....>
  template<class Pred, class TC = mp::identity, class FC = mp::always<false_>>
  using predicate = try_invoke<
    mp::fork<assume_unary<Pred>, mp::to_bool<>>,
    TC, FC>;
    
  // TODO output_type<Cmp> = number -> if_<subcontract<Cmp>, ....>
  template<class Cmp, class TC = mp::identity, class FC = mp::always<false_>>
  using compare = try_invoke<
    mp::fork<assume_binary<Cmp>, mp::to_bool<>>,
    TC, FC>;
}
