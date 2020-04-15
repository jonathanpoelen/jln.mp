#pragma once

#include "assume.hpp"
#include "../utility/always.hpp"
#include "../number/to_bool.hpp"
#include "../functional/fork.hpp"

namespace jln::mp::smp::concepts
{
  template<class Pred, class TC = mp::identity, class FC = mp::always<false_>>
  using predicate = try_invoke<
    mp::fork<assume_unary<Pred>, mp::to_bool<>>,
    TC, FC>;

  template<class Cmp, class TC = mp::identity, class FC = mp::always<false_>>
  using compare = try_invoke<
    mp::fork<assume_binary<Cmp>, mp::to_bool<>>,
    TC, FC>;
}
