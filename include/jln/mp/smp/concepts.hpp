#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/number/to_bool.hpp>
#include <jln/mp/functional/tee.hpp>

namespace jln::mp::smp::concepts
{
  // TODO optimize Pred = is<>, same<>, lift<std::is_same>, equal, less, not_
  // TODO optimize when FC = always
  // {unary, binary, mulary}_predicate
  template<class Pred, class TC = mp::identity, class FC = mp::always<false_>>
  using predicate = mp::try_<Pred, mp::try_or<mp::to_bool<TC>, FC>, FC>;

  template<class Pred, class FC = mp::always<false_>>
  using predicate_or = predicate<Pred, mp::identity, FC>;
}
