#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/functional/tee.hpp>
#include <jln/mp/smp/number/not.hpp>
#include <jln/mp/functional/not_fn.hpp>

namespace jln::mp::smp
{
  template <class F, class C = identity>
  using not_fn = contract<concepts::predicate<F, assume_positive_number<not_<C>>, violation>>;
}
