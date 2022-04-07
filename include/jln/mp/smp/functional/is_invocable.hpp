#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/functional/is_invocable.hpp>

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using is_invocable = contract<mp::is_invocable<subcontract<F>, assume_positive_number<C>>>;
}
